#pragma once

#include "Texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include <istream>
#include "SceneObject.h"

class Game;

class Enemy : public SceneObject
{
protected:
	float speed = 2;
	int frame = 0;
	int frameTime = 0;
	float frameMax = 2;
public:
	Enemy(Game* _game, std::istream& is);

	void update() override;
	void render() const override;
	Collision hit(const SDL_Rect& rect, bool fromPlayer) override;

	void defrost();
};

