#include "Coin.h"
#include "Game.h"

Coin::Coin(Game* _game, std::istream& is) :
	Pickable(_game)
{
	is >> pos;
	pos = pos * BlockTam;
	texture = game->getTexture(Game::COIN);
	height = BlockTam;
	width = BlockTam;
}

void Coin::update()
{
	if (game->changeFrame())
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

}

SceneObject* Coin::clone() const
{
	return new Coin(*this);
}
