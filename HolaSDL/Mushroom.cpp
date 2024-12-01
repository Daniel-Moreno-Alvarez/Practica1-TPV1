#include "Mushroom.h"
#include "Game.h"

Mushroom::Mushroom(Game* _game, Point2D _pos) : 
	Pickable(_game, _pos)
{
	texture = game->getTexture(Game::MUSHROOM);
	height = BlockTam;
	width = BlockTam;
	vel = Point2D(-speed, 0);
}

void Mushroom::update()
{
	vel = vel + gravity;

	pos.setY(pos.getY() + vel.getY());// Comprobación vertical
	SDL_Rect rectY{ pos.getX(), pos.getY() - BlockTam, BlockTam, BlockTam };
	Collision coll = game->checkCollision(rectY, false);
	if (coll) {
		if (vel.getY() > 0)
		{
			pos.setY(pos.getY() - coll.rect.h);// empujar hacia arriba
		}
		else {
			pos.setY(pos.getY() + coll.rect.h); // empujar hacia abajo
		}
		vel.setY(0.0f);
	}

	pos.setX(pos.getX() + vel.getX());// Comprobación horizontal
	SDL_Rect rectX{ pos.getX(), pos.getY() - BlockTam, BlockTam, BlockTam };
	coll = game->checkCollision(rectX, false);
	if (coll) {
		if (vel.getX() > 0)
		{
			pos.setX(pos.getX() - coll.rect.w);// empujar hacia izquierda
		}
		else {
			pos.setX(pos.getX() + coll.rect.w);// empujar hacia derecha
		}
		vel.setX(vel.getX() * -1);
	}

	//Si se sale del mapa por abajo
	if (pos.getY() > Game::WIN_HEIGHT || pos.getX() < game->getMapOffset() - BlockTam) {
		isAlive = false;
	}
}

void Mushroom::triggerAction()
{
	game->setPlayerState(PlayerState::SUPERMARIO_ST);
}

SceneObject* Mushroom::clone() const
{
	return new Mushroom(*this);
}