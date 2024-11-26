#include "Goomba.h"
#include "Game.h"

Goomba::Goomba(Game* _game, std::istream& is) : 
	Enemy(_game, is)
{
	texture = game->getTexture(Game::GOOMBA);
	height = BlockTam;
	width = BlockTam;
}