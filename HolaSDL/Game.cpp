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
	{"coin.png", 4, 1},
	{"lift.png", 1, 1},
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

	startObjects();
}

Game::~Game()
{
	deleteObjects();

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
				objectQueue.push_back(block);
				break;
			}
			case 'G': {
				Goomba* goomba = new Goomba(this, is);
				objectQueue.push_back(goomba);
				break;
			}
			case 'K': {
				Koopa* koopa = new Koopa(this, is);
				objectQueue.push_back(koopa);
				break;
			}
			case 'C': {
				Coin* coin = new Coin(this, is);
				objectQueue.push_back(coin);
				break;
			}
			case 'L': {
				Lift* lift = new Lift(this, is);
				objectQueue.push_back(lift);
				break;
			}
			default:
				break;
			}
		}
	}
	catch (const std::string& error)
	{
		throw std::string("Error al cargar el mapa .txt");
	}
}

Collision Game::checkCollision(const SDL_Rect& rect, Collision::Target target)
{
	Collision coll;
	for (auto obj : sceneObjects) {
		coll = obj->hit(rect, target);
		if (coll) {
			return coll;
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
	sceneObjects.push_back(mush);
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

void Game::startObjects()
{
	// Crea los objetos del juego
	tilemap = new TileMap(this, level);
	finalX = (tilemap->getFinalX() - 1) * BlockTam;
	loadMap();
}

void Game::deleteObjects()
{
	// Elimina los objetos del juego
	delete tilemap;
	delete player;

	for (auto obj : sceneObjects)
	{
		delete obj;
	}

	for (auto obj : objectQueue)
	{
		delete obj;
	}
	objectQueue.clear();
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

	renderLifes();

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	addVisibleObjects();

	for (auto it = sceneObjects.begin(); it != sceneObjects.end();) {
		SceneObject* obj = *it;
		// Si el objeto no es valido, eliminamos usando su ancla
		if (obj == nullptr) {
			obj->getListAnchor().unlink();
		}
		else {
			obj->update();
		}
		++it;
	}

	if (player->getPosition().getX() >= finalX) { // si llega al final
		if (level >= finalLevel) {
			seguir = false;
		}
		else {
			nextLevel();
		}
	}
	if (player->IsAlive() && player->getLifes() > 0) {
		player->update();
	}
	else {
		if (player->getLifes() > 0) {
			resetLevel();
		}
		else {
			seguir = false;
		}
	}

	if (player->getPosition().getX() >= mapOffset - BlockTam + WIN_WIDTH / 2) {

		mapOffset += 8;
	}

	updatescounter++;
	if (updatescounter >= ANIM_RANGE)
	{
		updatescounter = 0;
	}
}

void Game::resetLevel()
{
	for (auto obj : sceneObjects) {
		delete obj;
	}
	mapOffset = 0;
	nextObject = 0;
	player->restart();
}

void Game::nextLevel()
{
	deleteObjects();
	mapOffset = 0;
	nextObject = 0;
	level++;
	startObjects();
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
