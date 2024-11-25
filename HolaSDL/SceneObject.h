#pragma once

#include "Game.h"
#include "GameObject.h"
#include "Texture.h"
#include "Vector2D.h"

class SceneObject : public GameObject
{
protected:
	Point2D pos;
	Point2D vel;
	int height;
	int width;
	Texture* texture = nullptr;
	bool target;

	Collision tryToMove(const Point2D& speed, Collision::Target attack);
	SDL_Rect getCollisionRect() const;
	SDL_Rect getRenderRect() const;
	
public:
	SceneObject(Game* _game, Point2D _pos, Point2D _vel, int _h, int _w, bool _target) :
		GameObject(_game), pos(_pos), vel(_vel), height(_h), width(_w), target(_target)
	{};
	virtual Collision hit(const SDL_Rect& rect, bool fromPlayer);
};

