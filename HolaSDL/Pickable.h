#pragma once
#include "SceneObject.h"

class PlayState;

class Pickable : public SceneObject
{
public:
	Pickable(PlayState* _gameST, Point2D _pos);
	Pickable(PlayState* _gameST);

	void render() const override;
	Collision hit(const SDL_Rect& rect, Collision::Target target) override;

	virtual void triggerAction() = 0;
};

