#include "Mushroom.h"
#include "Game.h"

Mushroom::Mushroom(Game* _game, Point2D _pos) : game(_game), pos(_pos)
{
	texture = game->getTexture(Game::MUSHROOM);
	dir = Point2D(speed, 0);
}

void Mushroom::update()
{
	dir = dir + gravity;

	pos.setY(pos.getY() + dir.getY());// Comprobación vertical
	SDL_Rect rectY{ pos.getX(), pos.getY() - BlockTam, BlockTam, BlockTam };
	Collision coll = game->checkCollision(rectY, false);
	if (coll) {
		if (dir.getY() > 0)
		{
			pos.setY(pos.getY() - coll.rect.h);// empujar hacia arriba
		}
		else {
			pos.setY(pos.getY() + coll.rect.h); // empujar hacia abajo
		}
		dir.setY(0.0f);
	}

	pos.setX(pos.getX() + dir.getX());// Comprobación horizontal
	SDL_Rect rectX{ pos.getX(), pos.getY() - BlockTam, BlockTam, BlockTam };
	coll = game->checkCollision(rectX, false);
	if (coll) {
		if (dir.getX() > 0)
		{
			pos.setX(pos.getX() - coll.rect.w);// empujar hacia izquierda
		}
		else {
			pos.setX(pos.getX() + coll.rect.w);// empujar hacia derecha
		}
		dir.setX(dir.getX() * -1);
	}

	//Si se sale del mapa por abajo
	if (pos.getY() > Game::WIN_HEIGHT || pos.getX() < game->getMapOffset() - BlockTam) {
		isAlive = false;
	}
}

void Mushroom::render() const
{
	SDL_Rect rect = { pos.getX() - game->getMapOffset(), pos.getY() - BlockTam, BlockTam, BlockTam };
	texture->renderFrame(rect, 0, 0);
}

Collision Mushroom::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision coll;
	SDL_Rect actrect{ pos.getX(), pos.getY() - BlockTam, BlockTam, BlockTam };
	coll.collides = SDL_IntersectRect(&rect, &actrect, &coll.rect);
	if (coll && fromPlayer) {
		isAlive = false;
	}

	return coll;
}
