#pragma once

#include "Texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include <istream>
#include "Pickable.h"

class Mushroom : public Pickable
{
private:
	const float speed = 4;
public:
	Mushroom(PlayState* _gameST, Point2D _pos);

	void update() override;
	void triggerAction() override;

	SceneObject* clone() const override;
};

