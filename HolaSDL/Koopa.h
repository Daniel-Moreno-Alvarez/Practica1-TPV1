#pragma once

#include "Texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include <istream>

class Game;

class Koopa
{
	Game* game;
	Texture* texture;
private:
	const float speed = 2;
	const float auxscale = 2;
	Point2D pos;
	Point2D dir;
	int frame = 0;
	int frameTime = 0;
	const float frameMax = 2;
	bool isAlive = true;
	bool frozen = true;
public:
	Koopa(Game* _game, std::istream& is);
	void update();
	void render() const;
	Collision hit(const SDL_Rect& rect, bool fromPlayer);
	bool IsAlive() { return isAlive; };
	bool IsFrozzen() { return frozen; };
	void defrost();
};

