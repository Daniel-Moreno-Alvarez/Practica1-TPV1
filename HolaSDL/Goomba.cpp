#include "Goomba.h"
#include "Game.h"
#include "PlayState.h"

Goomba::Goomba(PlayState* _gameST, std::istream& is) :
	Enemy(_gameST, is)
{
	texture = playST->getGame()->getTexture(Game::GOOMBA);
	height = BlockTam;
	width = BlockTam;
}

SceneObject*
Goomba::clone() const
{
	return new Goomba(*this);
}