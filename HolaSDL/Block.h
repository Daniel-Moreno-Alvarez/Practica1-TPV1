#pragma once

#include "Texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include <istream>
#include "SceneObject.h"

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

class Block : public SceneObject
{
private:
	BlockTipe tipe;
	BlockAction action;
	int frameMax = 4;
public:
	Block(Game* _game, std::istream& is);
	void render() const override;
	void update() override;
	Collision hit(const SDL_Rect& rect, Collision::Target target) override;

	SceneObject* clone()const override;
};

