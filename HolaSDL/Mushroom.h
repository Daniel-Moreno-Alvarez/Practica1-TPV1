#pragma once

#include "Texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include <istream>
#include "Pickable.h"
class Game;

class Mushroom : public Pickable
{
private:
	const float speed = 4;
public:
	Mushroom(Game* _game, Point2D _pos);

	void update() override;
	void triggerAction() override;
};

