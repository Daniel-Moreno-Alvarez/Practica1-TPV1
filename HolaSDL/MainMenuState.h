#pragma once
#include "GameState.h"
#include "Button.h"
#include <vector>
class MainMenuState : public GameState
{
public:
	MainMenuState(Game* _game);
	virtual ~MainMenuState() = default;

	void render() const override;
	void update() override;

private:
	float auxposX = 0;
	const float nivel1posY = 280;
	const float nivel2posY = 330;
	const float salirposY = 430;
	void startMenu();
	void addButton(Button* _button);
	void loadLevel(int n);
};
