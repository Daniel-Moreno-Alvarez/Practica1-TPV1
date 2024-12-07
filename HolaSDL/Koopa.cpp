#include "Koopa.h"
#include "Game.h"

Koopa::Koopa(Game* _game, std::istream& is) :
	Enemy(_game, is)
{
	texture = game->getTexture(Game::KOOPA);
	height = BlockTam * SCALE;
	width = BlockTam;
}

SceneObject* Koopa::clone() const
{
	return new Koopa(*this);
}
