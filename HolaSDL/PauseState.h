#pragma once
#include "gameState.h"
#include "Button.h"

class PauseState : public GameState
{
public:
	PauseState(Game* _game, GameState* _gameState);
	virtual ~PauseState() = default;
	void update() override;
	void render() const override;
	void startMenu();
private:
	bool continuar = false;
	float auxposX = 0;
	const float volverposY = 180;
	const float continuarposY = 230;
	const float salirposY = 280;
	GameState* gameState;
};

