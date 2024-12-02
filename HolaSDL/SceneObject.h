#pragma once

#include "GameObject.h"
#include "Texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include "GameList.h"

class Game;

class SceneObject : public GameObject
{
protected:
	Point2D pos;
	Point2D vel;
	int height;
	int width;
	SDL_RendererFlip orientation = SDL_FLIP_NONE;
	Texture* texture = nullptr;
	bool target = false;
	bool isAlive = true;
	bool frozen = false;

	int frame = 0;
	int frameTime = 0;
	int frameMax;
	
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
	SceneObject(const SceneObject& other) :
		GameObject(other.game),
		pos(other.pos),
		vel(other.vel),
		width(other.width),
		height(other.height),
		texture(other.texture),
		isAlive(other.isAlive),
		frozen(other.frozen)
	{};

	virtual Collision hit(const SDL_Rect& rect, Collision::Target target) { return NO_COLLISION; };
	virtual SceneObject* clone() const = 0;

	Point2D getPosition() const { return pos; };
	bool IsAlive() const { return isAlive; };
	bool IsFrozen() const { return frozen; };

	Collision tryToMove(const Point2D& speed, Collision::Target attack);
	SDL_Rect getCollisionRect() const;
	SDL_Rect getRenderRect() const;

	GameList<SceneObject>::anchor anchor;
	void setListAnchor(GameList<SceneObject>::anchor&& _anchor) {
		anchor = std::move(_anchor);
	}
	GameList<SceneObject>::anchor& getListAnchor() {
		return anchor;
	}
};

