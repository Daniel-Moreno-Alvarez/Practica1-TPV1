#include "PlayState.h"
#include "Game.h"
#include "PauseState.h"

PlayState::~PlayState()
{
	deleteObjects();
}

void PlayState::startObjects()
{
	// Crea los objetos del juego
	tilemap = new TileMap(this, level);
	finalX = (tilemap->getFinalX() - 1) * BlockTam;
	infoBar = new InfoBar(this);
	loadMap();
}

void PlayState::deleteObjects()
{
	// Elimina los objetos del juego
	delete tilemap;
	delete player;
	delete infoBar;

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

void PlayState::loadMap()
{
	try
	{
		string i = to_string(level);
		ifstream file("../assets/maps/world" + i + ".txt");
		string line;
		getline(file, line);
		istringstream is(line);
		is >> r >> g >> b;
		SDL_SetRenderDrawColor(game->getRenderer(), r, g, b, 255);
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
		throw std::string("Error al cargar el mapa.txt");
	}
}

Collision PlayState::checkCollision(const SDL_Rect& rect, Collision::Target target)
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

void PlayState::addMushroom(Point2D _pos)
{
	Mushroom* mush = new Mushroom(this, _pos);
	addObject(mush);
}

void PlayState::addPoints(int _p)
{
	infoBar->setPoints(_p);
}

void
PlayState::render() const
{
	SDL_RenderClear(game->getRenderer());

	tilemap->render();
	for (auto obj : sceneObjects) {
		obj->render();
	}
	player->render();
	infoBar->render();

	SDL_RenderPresent(game->getRenderer());
}

void PlayState::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
	{
		PauseState* pause = new PauseState(game, this);
		game->getGameSTMachine()->pushState(pause);
	}
	else {
		player->handleEvent(event);
	}
}

void
PlayState::update()
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

	if (player->getPosition().getX() >= mapOffset - BlockTam + Game::WIN_WIDTH / 2) {

		mapOffset += 8;
	}

	if (!seguir)
	{
		game->getGameSTMachine()->popState();
	}

	updatescounter++;
}

void PlayState::resetLevel()
{
	for (auto obj : sceneObjects) {
		delete obj;
	}
	mapOffset = 0;
	nextObject = 0;
	player->restart();
}

void PlayState::nextLevel()
{
	deleteObjects();
	mapOffset = 0;
	nextObject = 0;
	level++;
	startObjects();
}

void
PlayState::addVisibleObjects()
{
	// Borde derecho del mapa (más una casilla)
	const int rightThreshold = mapOffset + Game::WIN_WIDTH + BlockTam;

	while (nextObject < objectQueue.size() && objectQueue[nextObject]->getPosition().getX() < rightThreshold)
		addObject(objectQueue[nextObject++]->clone());
}

void PlayState::addObject(SceneObject* object)
{
	sceneObjects.push_back(object);
}