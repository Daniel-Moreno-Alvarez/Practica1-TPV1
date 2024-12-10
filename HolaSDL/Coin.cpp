#include "Coin.h"
#include "Game.h"
#include "PlayState.h"

Coin::Coin(PlayState* _gameST, std::istream& is) :
	Pickable(_gameST)
{
	is >> pos;
	pos = pos * BlockTam;
	texture = playST->getGame()->getTexture(Game::COIN);
	height = BlockTam;
	width = BlockTam;
}

void Coin::update()
{
	frame = (playST->getFrames() / ANIM_RANGE) % frameMax;
}

void Coin::triggerAction()
{
	playST->addPoints(coinPoints);
}

SceneObject* Coin::clone() const
{
	return new Coin(*this);
}
