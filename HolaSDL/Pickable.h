#pragma once
#include "SceneObject.h"

class Game;

class Pickable : public SceneObject
{
public:
	Pickable(Game* _game, Point2D _pos);

	void render() const override;
	Collision hit(const SDL_Rect& rect, Collision::Target target) override;

	virtual void triggerAction() = 0;
};

