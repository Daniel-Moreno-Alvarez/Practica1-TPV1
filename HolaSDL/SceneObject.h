#pragma once

#include "GameObject.h"
#include "Texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include "GameList.h"

class PlayState;

class SceneObject : public GameObject
{
protected:
	PlayState* playST;

	Point2D pos;
	Point2D vel;
	int height;
	int width;
	SDL_RendererFlip orientation = SDL_FLIP_NONE;
	Texture* texture = nullptr;
	bool isAlive = true;
	bool frozen = false;

	int frame = 0;
	int frameTime = 0;
	int frameMax;
	
public:

	SceneObject(PlayState* _gameST) :
		GameObject(nullptr), playST(_gameST), pos(Point2D()), vel(Point2D()), height(0), width(0)
	{};
	SceneObject(PlayState* _gameST, Point2D _pos) :
		GameObject(nullptr), playST(_gameST), pos(_pos), vel(Point2D()), height(0), width(0)
	{};
	SceneObject(PlayState* _gameST, Point2D _pos, Point2D _vel, int _h, int _w) :
		GameObject(nullptr), playST(_gameST), pos(_pos), vel(_vel), height(_h), width(_w)
	{};
	SceneObject(const SceneObject& other) :
		GameObject(other.gameST),
		playST(other.playST),
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

