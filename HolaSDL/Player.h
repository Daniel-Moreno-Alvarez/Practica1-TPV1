#pragma once
#include "Texture.h"
#include "Vector2D.h"
#include <iostream> 
#include "Collision.h"
#include "SceneObject.h"
#include "EventHandler.h"

class GameState;

enum PlayerState {
	MARIO_ST,
	SUPERMARIO_ST,
};

class Player : public SceneObject, public EventHandler
{
private:
	const float speed = 8;
	const float jump = -32;
	const float minijump = -15;
	const float inmmuneLimit = 50;
	Point2D oripos;
	PlayerState actualState;
	bool onTheGround = false;
	bool isInmmune = false;
	int lastTime = 0;
	int lifes;
public:
	Player(PlayState* _gameST, Point2D _pos, int _lifes);
	Player(PlayState* _gameST, std::istream& is);

	void update() override;
	void render() const override;
	void handleEvent(const SDL_Event& event);
	void SetState(PlayerState pySt);
	void restart();
	
	SceneObject* clone() const override;
	PlayerState getState() const { return actualState; };
	Point2D getPosition() const { return pos; }
	int getLifes() const { return lifes; }
	bool IsInmmune() const { return isInmmune; };

	bool isOnTheground();
	void DieAimation();
};