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
	if (playST->changeFrame())
	{
		frame++;
		if (frame >= frameMax)
		{
			frame = 0;
		}
	}
}

void Coin::triggerAction()
{
	playST->addPoints(coinPoints);
}

SceneObject* Coin::clone() const
{
	return new Coin(*this);
}
