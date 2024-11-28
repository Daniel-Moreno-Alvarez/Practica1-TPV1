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
	if (!frozen)
	{
		// Acelra la velocidad con la gravedad
		vel = vel + gravity;

		// Velocidad en este ciclo (no siempre avanza lateralmente)
		Point2D realSpeed = vel;

		// Intenta moverse
		Collision collision = tryToMove(vel, Collision::PLAYER);

		// Si toca un objeto en horizontal cambia de dirección
		if (collision.horizontal)
			vel.setX(-vel.getX());

		// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
		if (collision.vertical)
			vel.setY(0);

		// Si se sale del mapa por abajo
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
	else {
		defrost();
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
