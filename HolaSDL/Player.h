#pragma once
#include "Texture.h"
#include "Vector2D.h"
#include <iostream> 
#include "Collision.h"
#include "SceneObject.h"

class Game;

enum PlayerState {
	MARIO_ST,
	SUPERMARIO_ST,
};

class Player : public SceneObject
{
private:
	const float speed = 8;
	const float jump = -25;
	const float minijump = -10;
	const float inmmuneLimit = 50;
	Point2D oripos;
	SDL_RendererFlip orientation = SDL_FLIP_NONE;
	PlayerState actualState;
	float auxscale = 2;
	bool onTheGround;
	bool isInmmune = false;
	int lastTime = 0;
	int lifes;
public:
	Player(Game* _game, Point2D _pos, int _lifes);
	Player(Game* _game, std::istream& is);

	void update() override;
	void render() const override;
	Collision hit(const SDL_Rect& rect, bool fromPlayer);
	void handleEvent(const SDL_Event& event);
	void SetState(PlayerState pySt);
	void restart();
	
	PlayerState getState() { return actualState; };
	Point2D getPosition() const { return pos; }
	int getLifes() const { return lifes; }
	bool IsInmmune() const { return isInmmune; };
};