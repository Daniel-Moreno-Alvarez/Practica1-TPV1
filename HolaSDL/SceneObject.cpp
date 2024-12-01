#include "SceneObject.h"
#include "Game.h"

Collision SceneObject::tryToMove(const Point2D& speed, Collision::Target attack) {
	Collision collision;
	SDL_Rect rect = getCollisionRect();

	// Intenta moverse en vertical
	if (speed.getY() != 0) {
		rect.y += speed.getY();

		collision = game->checkCollision(rect, attack);

		// Cantidad que se ha entrado en el obstáculo (lo que hay que deshacer)
		int fix = collision.vertical * (speed.getY() > 0 ? 1 : -1);
		pos.setY(pos.getY() + speed.getY() - fix);

		// Obs: a ? b : c es el operador ternario: vale b si a es cierto y c en caso contrario

		rect.y -= fix; // recoloca la caja para la siguiente colisión
	}

	collision.horizontal = 0; // la horizontal del choque vertical da igual

	// Intenta moverse en horizontal
	// (podría ser conveniente comprobar colisiones incluso aunque el objeto estuviera parado)
	if (speed.getX() != 0) {
		rect.x += speed.getX();

		Collision partial = game->checkCollision(rect, attack);

		// Copia la información de esta colisión a la que se devolverá
		collision.horizontal = partial.horizontal;

		if (partial.result == Collision::DAMAGE)
			collision.result = Collision::DAMAGE;

		float x = speed.getX() - collision.horizontal * (speed.getX() > 0 ? 1 : -1);
		pos.setX(pos.getX() + x);
	}

	return collision;
}

SDL_Rect
SceneObject::getCollisionRect() const
{
	return SDL_Rect{
		int(pos.getX()),
		int(pos.getY()) - height,  // la referencia es la esquina inferior izquierda
		width,
		height
	};
}

SDL_Rect
SceneObject::getRenderRect() const
{
	return SDL_Rect{
		int(pos.getX()) - game->getMapOffset(),  // coordenadas de la ventana
		int(pos.getY()) - height,
		width,
		height
	};
}