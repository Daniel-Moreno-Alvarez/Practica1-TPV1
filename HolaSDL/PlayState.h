#pragma once
#include "gameState.h"
#include <vector>
#include "Game.h"
#include "GameList.h"
#include "Texture.h"
#include "TileMap.h"
#include "Player.h"
#include "Block.h"
#include "Collision.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Mushroom.h"
#include "Coin.h"
#include "Lift.h"
#include "InfoBar.h"
#include "SDLError.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"

class PlayState : public GameState
{
protected:
	// Interruptor para terminar el juego
	bool seguir;
	//offset del mapa
	int mapOffset = 0;
	// Objetos del juego

	GameList<SceneObject> sceneObjects;

	std::vector<SceneObject*> objectQueue;
	int nextObject;

	TileMap* tilemap;
	Player* player;
	InfoBar* infoBar;

	unsigned int level = 1;
	const unsigned int finalLevel = 2;
	int r, g, b;
	int finalX;

	int updatescounter = 0;
public:
	PlayState(Game* _game) : GameState(_game) {
		startObjects();
	};

	void startObjects();
	void deleteObjects();

	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event& event) override;
	void loadMap();
	Collision checkCollision(const SDL_Rect& rect, Collision::Target target);
	void addMushroom(Point2D _pos);
	void addPoints(int _p);

	// Geters
	int getMapOffset() const { return mapOffset; };
	PlayerState getPlayerState() { return player->getState(); };

	Player* getPlayer() const { return player; };

	bool changeFrame() const { return updatescounter == 0; };

	// Seters
	void setPlayerState(PlayerState pySt) { player->SetState(pySt); };
	void resetLevel();
	void nextLevel();

	void addVisibleObjects();
	void addObject(SceneObject* object);
};

