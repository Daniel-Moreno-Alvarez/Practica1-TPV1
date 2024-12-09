#include "Koopa.h"
#include "Game.h"
#include "PlayState.h"

Koopa::Koopa(PlayState* _gameST, std::istream& is) :
	Enemy(_gameST, is)
{
	texture = playST->getGame()->getTexture(Game::KOOPA);
	height = BlockTam * SCALE;
	width = BlockTam;
}

SceneObject* Koopa::clone() const
{
	return new Koopa(*this);
}
