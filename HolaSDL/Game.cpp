#include <string>

#include "Game.h"

using namespace std;

// Formato de la especificacion de una textura
struct TextureSpec
{
	const char* name;	// Ruta del archivo
	uint numColumns;	// Número de frames por fila
	uint numRows;		// Número de frames por columna
};

// Directorio raíz de los archivos de textura
const string textureRoot = "../assets/images/";

// Especificacion de las texturas del juego
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec
	{"background.png", 9, 7},
	{"blocks.png", 6, 1},
	{"firemario.png", 21, 1},
	{"goomba.png", 3, 1},
	{"koopa.png", 4, 1},
	{"mario.png", 12, 1},
	{"mushroom.png", 1, 1},
	{"piranha.png", 2, 1},
	{"plant.png", 4, 1},
	{"shell.png", 2, 1},
	{"star.png", 4, 1},
	{"supermario.png", 22, 1},
};

const array<std::string, Game::NUM_MAPS> mapsSpec
{
	"../assets/maps/world1.csv",
	"../assets/maps/world1.txt",
	"../assets/maps/world2.csv",
	"../assets/maps/world2.txt",
};

Game::Game()
 : seguir(true)
{
	// Inicializa la SDL
	try
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		window = SDL_CreateWindow("SUPER MARIO",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH,
			WIN_HEIGHT,
			SDL_WINDOW_SHOWN);

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}
	catch (const std::string& error)
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		throw "Error al cargar SDL";
	}

	if (window == nullptr || renderer == nullptr)
		throw "Error cargando SDL"s;

	// Carga las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i) {
		try {
			textures[i] = new Texture(renderer,
				(textureRoot + textureSpec[i].name).c_str(),
				textureSpec[i].numRows,
				textureSpec[i].numColumns);
		}
		catch (const std::string& error)
		{
			throw "Error al cargar la textura " + string(textureSpec[i].name);
		}
	}

	// Carga los mapas
	for (int i = 0; i < NUM_MAPS; ++i) {
		maps[i] = mapsSpec[i];
	}

	// Crea los objetos del juego
	tilemap = new TileMap(this, level);
	finalX = tilemap->getFinalX() * BlockTam;
	goombas = new vector<Goomba*>();
	koopas = new vector<Koopa*>();
	blocks = new vector<Block*>();
	mushrooms = new vector<Mushroom*>();
	loadMap();
}

Game::~Game()
{
	// Elimina los objetos del juego
	delete tilemap;
	delete player;

	for (Block* block : *blocks) {
		delete block;
	}
	delete blocks;

	for (Goomba* goomba : *goombas) {
		delete goomba;
	}
	delete goombas;

	for (Koopa* koopa : *koopas) {
		delete koopa;
	}
	delete koopas;

	for (Mushroom* mush : *mushrooms) {
		delete mush;
	}
	delete mushrooms;

	// Elimina las texturas
	for (Texture* texture : textures) {
		delete texture;
	}

	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::loadMap()
{
	try
	{
		string i = to_string(level);
		ifstream file("../assets/maps/world" + i + ".txt");

	string line;
	getline(file, line);
	istringstream is(line);
	is >> r >> g >> b;
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	while (getline(file, line)) {
		istringstream is(line);
		char type;
		is >> type;
		switch (type)
		{
		case 'M': {
			player = new Player(this, is);
			break;
		}
		case 'B': {
			Block* block = new Block(this, is);
			blocks->push_back(block);
			objectQueue.push_back(block);
			break;
		}
		case 'G': {
			Goomba* goomba = new Goomba(this, is);
			goombas->push_back(goomba);
			objectQueue.push_back(goomba);
			break;
		}
		case 'K': {
			Koopa* koopa = new Koopa(this, is);
			koopas->push_back(koopa);
			objectQueue.push_back(koopa);
			break;
		}
		default:
			break;
		}
	}
	}
	catch (const std::string& error)
	{
		throw std::string("Error al cargar " + getMap(WORLD1TXT));
	}
}

Collision Game::checkCollision(const SDL_Rect& rect, Collision::Target target)
{
	Collision coll;
	for (auto obj : sceneObjects) {
		if (true)
		{
			coll = obj->hit(rect, target);
			if (coll) {
				return coll;
			}
		}
	}
	coll = tilemap->hit(rect, target);
	if (coll) {
		return coll;
	}
	return NO_COLLISION;
}

void Game::addMushroom(Point2D _pos)
{
	Mushroom* mush = new Mushroom(this, _pos);
	mushrooms->push_back(mush);
}

void Game::renderLifes()
{
	int tam = 20;
	int offset = 5;
	for (int i = 0; i < player->getLifes(); i++) {
		SDL_Rect rect = { offset + (tam + offset) * i, offset, tam,tam};
		getTexture(MARIO)->renderFrame(rect, 0, 0);
	}
}

void
Game::run()
{
	// Bucle principal del juego
	while (seguir) {
		// Marca de tiempo del inicio de la iteración
		uint32_t inicio = SDL_GetTicks();

		update();// Actualiza el estado de los objetos del juego
		render();       // Dibuja los objetos en la venta
		handleEvents(); // Maneja los eventos de la SDL

		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		// Duerme el resto de la duraci�n del frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
}

void
Game::render()
{
	SDL_RenderClear(renderer);

	tilemap->render();
	player->render();

	for (auto obj : sceneObjects) {
		obj->render();
	}

	for (Mushroom* mush : *mushrooms) {
		mush->render();
	}

	renderLifes();

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	if (player->getPosition().getX() >= finalX) { // si llega al final
		seguir = false;
	}

	if (player->IsAlive() && player->getLifes() > 0) {
		player->update();
	}
	else {
		if (player->getLifes() > 0) {
			mapOffset = 0;
			player->restart();
		}
		else {
			seguir = false;
		}
	}

	if (player->getPosition().getX() >= mapOffset - BlockTam + WIN_WIDTH / 2) {

		mapOffset += 8;
	}

	for (auto obj : sceneObjects)
	{
		obj->update();
	}

	for (auto it = mushrooms->begin(); it != mushrooms->end(); ) {
		Mushroom* Mush = *it;

		if (Mush->IsAlive()) {
			Mush->update();
			++it;
		}
		else {
			delete Mush;
			it = mushrooms->erase(it);
		}
	}
	addVisibleObjects();
}

void
Game::addVisibleObjects()
{
	// Borde derecho del mapa (m�s una casilla)
	const int rightThreshold = mapOffset + WIN_WIDTH + BlockTam;

	while (nextObject < objectQueue.size() && objectQueue[nextObject]->getPosition().getX() < rightThreshold)
		addObject(objectQueue[nextObject++]->clone());
}

void Game::addObject(SceneObject* object)
{
	sceneObjects.push_back(object);
}

void
Game::handleEvents()
{
	// Procesamiento de eventos
	SDL_Event evento;

	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT)
			seguir = false;
		else if (evento.type == SDL_KEYDOWN || evento.type == SDL_KEYUP) {
			player->handleEvent(evento);
		}
	}
} 
