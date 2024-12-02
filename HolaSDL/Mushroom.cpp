#include "Mushroom.h"
#include "Game.h"

Mushroom::Mushroom(Game* _game, Point2D _pos) : 
	Pickable(_game, _pos)
{
	texture = game->getTexture(Game::MUSHROOM);
	height = BlockTam;
	width = BlockTam;
	vel = Point2D(speed, 0);
}

void Mushroom::update()
{
	// Acelra la velocidad con la gravedad
	vel = vel + gravity;

	// Intenta moverse
	Collision collision = tryToMove(vel, Collision::PLAYER);

	// Si toca un objeto en horizontal cambia de dirección
	if (collision.horizontal)
		vel.setX(-vel.getX());

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
		vel.setY(0);

	// Si se sale de la ventana
	if (pos.getY() > Game::WIN_HEIGHT || 
		pos.getX() < game->getMapOffset() - BlockTam || 
		pos.getY() > Game::WIN_HEIGHT || 
		pos.getX() < game->getMapOffset() - BlockTam) {
		delete this;
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