#pragma once

#include "Texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include <istream>
class Game;

class Mushroom
{
	Game* game;
	Texture* texture;
private:
	const float speed = 4;
	Point2D pos;
	Point2D dir;
	int frame = 0;
	int frameTime = 0;
	const float frameMax = 2;
	bool isAlive = true;
public:
	Mushroom(Game* _game, Point2D _pos);
	void update();
	void render() const;
	Collision hit(const SDL_Rect& rect, bool fromPlayer);
	bool IsAlive() { return isAlive; };

};

