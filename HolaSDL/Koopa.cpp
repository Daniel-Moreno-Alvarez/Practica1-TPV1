#include "Koopa.h"
#include "Game.h"

Koopa::Koopa(Game* _game, std::istream& is) : game(_game)
{
	texture = game->getTexture(Game::KOOPA);
	is >> pos;
	pos = pos * BlockTam;
	dir = Point2D(-speed, 0);
}

void Koopa::update()
{
	dir = dir + gravity;

	pos.setY(pos.getY() + dir.getY());// Comprobación vertical
	SDL_Rect rectY{ pos.getX(), pos.getY() - BlockTam * auxscale, BlockTam, BlockTam * auxscale };
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
	SDL_Rect rectX{ pos.getX(), pos.getY() - BlockTam * auxscale, BlockTam, BlockTam * auxscale };
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

	//actualiza el frame
	frameTime++;
	if (frameTime >= 10)
	{
		frame++;
		if (frame >= frameMax)
		{
			frame = 0;
		}
		frameTime = 0;
	}
}

void Koopa::render() const
{
	SDL_Rect rect = { pos.getX() - game->getMapOffset(), pos.getY() - BlockTam * auxscale, BlockTam, BlockTam * auxscale };
	texture->renderFrame(rect, 0, frame);
}

Collision Koopa::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision coll;
	SDL_Rect actrect{ pos.getX(), pos.getY() - BlockTam, BlockTam, BlockTam };
	coll.collides = SDL_IntersectRect(&rect, &actrect, &coll.rect);
	if (coll && fromPlayer) {
		if (coll.rect.y <= actrect.y && coll.rect.w > BlockTam / 8 && coll.rect.h < BlockTam * 3 / 4)
		{
			isAlive = false;
			coll.damages = false;
		}
		else {
			coll.damages = true;
		}
	}

	return coll;
}

void Koopa::defrost()
{
	if (pos.getX() < game->getMapOffset() + Game::WIN_WIDTH) {
		frozen = false;
	}
}