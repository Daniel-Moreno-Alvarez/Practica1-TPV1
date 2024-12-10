#pragma once
#include "gameState.h"
#include "Button.h"
#include "Texture.h"

class EndState : public GameState
{
public:
	EndState(Game* _game, bool _win);
	virtual ~EndState() = default;

	void render() const override;
	void update() override;
	void startMenu();
private:
	bool win;
	float auxposX = 0;
	const float tituloposY = 180;
	const float volverposY = 230;
	const float salirposY = 280;
	SDL_Rect rect;
	Texture* texture;
};

