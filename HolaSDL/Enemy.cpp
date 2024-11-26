#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* _game, std::istream& is) :
	SceneObject(_game, false)
{
	is >> pos;
	pos = pos * BlockTam;
	vel = Point2D(-speed, 0);
	frozen = true;
}

void Enemy::update()
{
	vel = vel + gravity;

	pos.setY(pos.getY() + vel.getY());// Comprobación vertical
	SDL_Rect rectY = getCollisionRect();
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
	SDL_Rect rectX = getCollisionRect();
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

	if (pos.getX() < game->getMapOffset() + Game::WIN_WIDTH) {
		frozen = false;
	}
}

void Enemy::render() const
{
	SDL_Rect rect = getRenderRect();
	texture->renderFrame(rect, 0, frame);
}

Collision Enemy::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision coll;
	SDL_Rect actrect{ pos.getX(), pos.getY() - BlockTam, BlockTam, BlockTam };
	coll.collides = SDL_IntersectRect(&rect, &actrect, &coll.rect);
	if (coll && fromPlayer) {
		//Comprobacion de que la collision ha sido desde arriba
		if (coll.rect.y <= actrect.y && coll.rect.w > BlockTam / 8 && coll.rect.h < BlockTam * 3 / 4)
		{
			isAlive = false;
		}
		else {
			coll.damages = true;
		}
	}

	return coll;
}

void Enemy::defrost()
{
	if (pos.getX() < game->getMapOffset() + Game::WIN_WIDTH) {
		frozen = false;
	}
}
