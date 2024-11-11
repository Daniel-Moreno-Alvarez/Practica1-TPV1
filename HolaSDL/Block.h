#pragma once

#include "Texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include <istream>

class Game;

enum BlockTipe {
	BRICK,
	SURPRISE,
	VOID,
	HIDDEN
};

enum BlockAction {
	POWERUP,
	COIN, 
	NONE
};

class Block
{
	Game* game;
	Texture* texture;
private:
	Point2D pos;
	BlockTipe tipe;
	BlockAction action;
	int frame = 0;
	int frameTime = 0;
	const int frameMax = 4;
	bool isAlive = true;
public:
	Block(Game* _game, std::istream& is);
	void render() const;
	void update();
	Collision hit(const SDL_Rect& rect, bool fromPlayer);
	bool IsAlive() { return isAlive; };
};

