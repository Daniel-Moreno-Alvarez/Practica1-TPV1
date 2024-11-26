#pragma once

#include "GameObject.h"
#include "Texture.h"
#include "Vector2D.h"
#include "Collision.h"

class Game;

class SceneObject : public GameObject
{
protected:
	Point2D pos;
	Point2D vel;
	int height;
	int width;
	Texture* texture = nullptr;
	bool target = false;
	bool isAlive = true;
	bool frozen = false;

	Collision tryToMove(const Point2D& speed, Collision::Target attack);
	SDL_Rect getCollisionRect() const;
	SDL_Rect getRenderRect() const;

	void SetTexture();
	
public:
	SceneObject(Game* _game, bool _target) :
		GameObject(_game), pos(Point2D()), vel(Point2D()), height(0), width(0), target(_target)
	{};
	SceneObject(Game* _game, Point2D _pos,  bool _target) :
		GameObject(_game), pos(_pos), vel(Point2D()), height(0), width(0), target(_target)
	{};
	SceneObject(Game* _game, Point2D _pos, Point2D _vel, int _h, int _w, bool _target) :
		GameObject(_game), pos(_pos), vel(_vel), height(_h), width(_w), target(_target)
	{};

	virtual Collision hit(const SDL_Rect& rect, bool fromPlayer) = 0;
	
	bool IsAlive() const { return isAlive; };
	bool IsFrozen() const { return frozen; };
};

