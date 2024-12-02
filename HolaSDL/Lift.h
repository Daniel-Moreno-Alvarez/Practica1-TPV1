#pragma once
#include "SceneObject.h"
#include <iostream> 

class Lift : public SceneObject
{
public:
	Lift(Game* _game, std::istream& is);

	void render() const override;
	void update() override;
	virtual Collision hit(const SDL_Rect& rect, Collision::Target target) override;

	virtual SceneObject* clone() const override;
};