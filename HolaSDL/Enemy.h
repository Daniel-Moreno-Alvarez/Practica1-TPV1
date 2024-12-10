#pragma once

#include "Texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include <istream>
#include "SceneObject.h"

class PlayState;

class Enemy : public SceneObject
{
protected:
	float speed = 2;
	int frame = 0;
	int frameTime = 0;
	int frameMax = 2;
public:
	Enemy(PlayState* _gameST, std::istream& is);

	void update() override;
	void render() const override;
	Collision hit(const SDL_Rect& rect, Collision::Target target) override;
};

