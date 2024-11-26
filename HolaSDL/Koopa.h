#pragma once

#include "Texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include <istream>
#include "Enemy.h"

class Game;

class Koopa : public Enemy
{
public:
	Koopa(Game* _game, std::istream& is);
	SceneObject* clone() const override;
};

