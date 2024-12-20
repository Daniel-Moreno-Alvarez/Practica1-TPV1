#include "Mushroom.h"
#include "Game.h"
#include "PlayState.h"

Mushroom::Mushroom(PlayState* _gameST, Point2D _pos) :
	Pickable(_gameST, _pos)
{
	texture = playST->getGame()->getTexture(Game::MUSHROOM);
	height = BlockTam;
	width = BlockTam;
	vel = Point2D(speed, 0);
}

void Mushroom::update()
{
	// Acelra la velocidad con la gravedad
	vel = vel + gravity;
	if (vel.getY() >= MAX_SPEED) {
		vel.setY(MAX_SPEED);
	}

	// Intenta moverse
	Collision collision = tryToMove(vel, Collision::PLAYER);

	// Si toca un objeto en horizontal cambia de direcci�n
	if (collision.horizontal)
		vel.setX(-vel.getX());

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
		vel.setY(0);

	// Si se sale de la ventana
	if (pos.getY() > Game::WIN_HEIGHT || 
		pos.getX() < playST->getMapOffset() - BlockTam) {
		delete this;
	}
}

void Mushroom::triggerAction()
{
	playST->addPoints(mushroomPoints);
	playST->setPlayerState(PlayerState::SUPERMARIO_ST);
}

SceneObject* Mushroom::clone() const
{
	return new Mushroom(*this);
}