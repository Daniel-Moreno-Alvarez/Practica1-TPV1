#include "InfoBar.h"
#include "Game.h"

InfoBar::InfoBar(Game* _game) : GameObject(_game)
{ 
	numeros = game->getTexture(Game::NUMBERS);
}

void InfoBar::render() const
{
	// vidas
	for (int i = 0; i < game->getPlayer()->getLifes(); i++)
	{
		SDL_Rect rect = { offset + (tam + offset) * i, offset, tam,tam };
		game->getTexture(Game::MARIO)->renderFrame(rect, 0, 0);
	}
	// puntos
	if (points == 0) {
		SDL_Rect rect = { Game::WIN_WIDTH - (tam + offset), offset, tam, tam };
		numeros->renderFrame(rect, 0, 0);
		return;
	}
	int pointsaux = points;
	int i = 1;
	while (pointsaux != 0)
	{
		SDL_Rect rect = { Game::WIN_WIDTH - (tam + offset) * i, offset, tam,tam };
		unsigned int num = pointsaux % 10;
		numeros->renderFrame(rect, 0, num);
		pointsaux /= 10;
		i++;
	}
}