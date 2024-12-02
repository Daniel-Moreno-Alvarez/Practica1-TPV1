#include "Player.h"
#include "Game.h"

constexpr int FRAME_PERIOD = 20;

Player::Player(Game* _game, Point2D _pos, int _lifes) : 
	SceneObject(_game, _pos, {0,0}, 0, 0),
	lifes(_lifes)
{
	SetState(MARIO_ST);
	oripos = pos;
}

Player::Player(Game* _game, std::istream& is) :
	SceneObject(_game, {0,0}, {0,0}, 0, 0)
{
	SetState(MARIO_ST);
	is >> pos >> lifes;
	pos = pos * BlockTam;
	oripos = pos;
}

void Player::update()
{
	vel = vel + gravity;
	if (vel.getY() >= MAX_SPEED) {
		vel.setY(MAX_SPEED);
	}

	Collision coll = tryToMove(vel, Collision::ENEMIES);

	if (coll.horizontal) {
		vel.setX(0);
	}
	if (coll.vertical) {
		if (vel.getY() > 0) {
			onTheGround = true;
		}
		vel.setY(0);
	}
	else {
		onTheGround = false;
	}

	// Para que no se salga del mapa
	if (pos.getX() < game->getMapOffset()) {
		pos.setX(game->getMapOffset());
	}

	if ((coll.damages) && !isInmmune) { // comprobar el daño
		if (actualState == MARIO_ST) {
			isAlive = false;
		}
		else {
			SetState(MARIO_ST);
			isInmmune = true;
		}
	}
	else if (coll.isEnemy) {
		vel.setY(minijump);
	}
	// Comprueba si se ha salido del mapa por abajo
	if (pos.getY() > Game::WIN_HEIGHT) {
		isAlive = false;
	}

	if (isInmmune) { // contador de inmunidad
		lastTime++;
		if (lastTime >= inmmuneLimit) {
			isInmmune = false;
			lastTime = 0;
		}
	}
}

void Player::render() const
{
	if (!isInmmune || lastTime % 2 == 0) {
		SDL_Rect rect = getRenderRect();

		if (!isAlive)
		{
			texture->renderFrame(rect, 0, 1);
		}
		else if (vel.getX() == 0 && vel.getY() == 0) {
			texture->renderFrame(rect, 0, 0, orientation);
		}
		else if (vel.getY() != 0) {
			texture->renderFrame(rect, 0, 6, orientation);
		}
		else {
			int x = pos.getX();
			texture->renderFrame(rect, 0, 2 + x % 3, orientation);
		}
	}
}

void Player::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_d) {
			vel.setX(speed);
			orientation = SDL_FLIP_NONE;
		}
		else if (event.key.keysym.sym == SDLK_a && pos.getX() > game->getMapOffset()) {
			vel.setX(-speed);
			orientation = SDL_FLIP_HORIZONTAL;
		}
		else {
			vel.setX(0);
		}

		if (event.key.keysym.sym == SDLK_SPACE && onTheGround) {
			vel.setY(jump);
			onTheGround = false;
		}
	}
	else {
		vel.setX(0);
	}
}

void Player::SetState(PlayerState pySt)
{
	switch (pySt)
	{
	case MARIO_ST:
		actualState = MARIO_ST;
		texture = game->getTexture(Game::MARIO);
		break;
	case SUPERMARIO_ST:
		actualState = SUPERMARIO_ST;
		texture = game->getTexture(Game::SUPERMARIO);
		break;
	default:
		break;
	}
	height = texture->getFrameHeight() * SCALE;
	width = texture->getFrameWidth() * SCALE;
}

void Player::restart()
{
	lifes--;
	isAlive = true;
	SetState(MARIO_ST);
	pos = oripos;
	vel = Point2D();
}

SceneObject* Player::clone() const
{
	return new Player(*this);
}
