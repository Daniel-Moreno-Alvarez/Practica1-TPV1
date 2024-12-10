#include "Enemy.h"
#include "Game.h"
#include "PlayState.h"

Enemy::Enemy(PlayState* _gameST, std::istream& is) :
	SceneObject(_gameST)
{
	is >> pos;
	pos = pos * BlockTam;
	vel = Point2D(-speed, 0);
}

void Enemy::update()
{
	// Acelra la velocidad con la gravedad
	vel = vel + gravity;
	if (vel.getY() >= MAX_SPEED) {
		vel.setY(MAX_SPEED);
	}

	// Intenta moverse
	Collision collision = tryToMove(vel, Collision::PLAYER);

	// Si toca un objeto en horizontal cambia de dirección
	if (collision.horizontal) {
		if (orientation == SDL_FLIP_NONE) {
			orientation = SDL_FLIP_HORIZONTAL;
		}
		else {
			orientation = SDL_FLIP_NONE;
		}
		vel.setX(-vel.getX());
	}

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
		vel.setY(0);

	//actualiza el frame
	
	if (playST->changeFrame())
	{
		frame++;
		if (frame >= frameMax)
		{
			frame = 0;
		}
	}
	// Si se sale del mapa por abajo
	if (pos.getY() > Game::WIN_HEIGHT || pos.getX() < playST->getMapOffset() - BlockTam) {
		delete this;
	}
}

void Enemy::render() const
{
	SDL_Rect rect = getRenderRect();
	texture->renderFrame(rect, 0, frame, orientation);
}

Collision Enemy::hit(const SDL_Rect& rect, Collision::Target target)
{
	if (target == Collision::ENEMIES && playST->getPlayer()->IsInmmune()) {
		return NO_COLLISION;
	}
	if (target == Collision::PLAYER) {
		return NO_COLLISION;
	}
	Collision coll;
	SDL_Rect actrect = getCollisionRect();
	coll.collides = SDL_IntersectRect(&rect, &actrect, &coll.rect);
	if (coll) {
		if (target == Collision::ENEMIES)
		{
			//Comprobacion de que la collision ha sido desde arriba
			if (coll.rect.y <= actrect.y && coll.rect.w > BlockTam4 && coll.rect.h < BlockTam4 * 3)
			{
				playST->addPoints(enemyPoints);
				coll.isEnemy = true;
				delete this;
			}
			else {
				coll.damages = true;
			}
		}
	}

	return coll;
}
