#include "Player.h"
#include "Game.h"

constexpr int FRAME_PERIOD = 20;

Player::Player(Game* _game, Point2D _pos, int _lifes) : game(_game),  pos(_pos), lifes(_lifes)
{
	SetState(MARIO_ST);
	onTheGround = false;
}

Player::Player(Game* _game, std::istream& is) : game(_game)
{
	SetState(MARIO_ST);
	is >> pos >> lifes;
	pos = pos * BlockTam;
	onTheGround = false;
}

void Player::update()
{
	dir = dir + gravity;

	bool damage = false;

	pos.setY(pos.getY() + dir.getY());// Comprobación vertical
	SDL_Rect rectY{ pos.getX(), pos.getY() - texture->getFrameHeight() * auxscale,
		texture->getFrameWidth() * auxscale, texture->getFrameHeight() * auxscale };
	Collision coll = game->checkCollision(rectY, true);
	if (coll) {
		if (dir.getY() > 0)
		{
			pos.setY(pos.getY() - coll.rect.h);// empujar hacia arriba
			onTheGround = true;
		}
		else {
			pos.setY(pos.getY() + coll.rect.h); // empujar hacia abajo
		}
		dir.setY(0.0f);
	}
	if (coll.damages)
	{
		damage = true;
	}

	pos.setX(pos.getX() + dir.getX());// Comprobación horizontal
	SDL_Rect rectX{ pos.getX(), pos.getY() - texture->getFrameHeight() * auxscale,
		texture->getFrameWidth() * auxscale, texture->getFrameHeight() * auxscale };
	coll = game->checkCollision(rectX, true);
	if (coll) {
		if (dir.getX() > 0)
		{
			pos.setX(pos.getX() - coll.rect.w);// empujar hacia izquierda
		}
		else {
			pos.setX(pos.getX() + coll.rect.w);// empujar hacia derecha
		}
		dir.setX(0.0f);
	}
	if (coll.damages)
	{
		damage = true;
	}

	if (damage)
	{
		if (actualState == MARIO_ST) {
			isAlive = false;
		}
		else {
			SetState(MARIO_ST);
		}
	}

	// Para que no se salga del mapa
	if (pos.getX() < game->getMapOffset()) {
		pos.setX(game->getMapOffset());
	}

	// Comprueba si se ha salido del mapa por abajo
	if (pos.getY() > Game::WIN_HEIGHT) {
		isAlive = false;
	}
}

void Player::render() const
{
	SDL_Rect rect{ pos.getX() - game->getMapOffset(), pos.getY() - texture->getFrameHeight() * auxscale,
		 texture->getFrameWidth() * auxscale, texture->getFrameHeight() * auxscale };

	if (!isAlive)
	{
		texture->renderFrame(rect, 0, 1);
	}
	else if (dir.getX() == 0 && dir.getY() == 0) {
		texture->renderFrame(rect, 0, 0, orientation);
	}
	else if (dir.getY() != 0) {
		texture->renderFrame(rect, 0, 6, orientation);
	}
	else {
		int x = pos.getX();
		texture->renderFrame(rect, 0, 2 + x % 3, orientation);
	}
}

void Player::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_d) {
			dir.setX(speed);
			orientation = SDL_FLIP_NONE;
		}
		else if (event.key.keysym.sym == SDLK_a && pos.getX() > game->getMapOffset()) {
			dir.setX(-speed);
			orientation = SDL_FLIP_HORIZONTAL;
		}
		else {
			dir.setX(0);
		}

		if (event.key.keysym.sym == SDLK_SPACE && onTheGround) {
			dir.setY(jump);
			onTheGround = false;
		}
	}
	else {
		dir.setX(0);
	}
}

void Player::SetState(PlayerState pySt)
{
	switch (pySt)
	{
	case MARIO_ST:
		actualState = MARIO_ST;
		texture = game->getTexture(Game::MARIO);
		auxscale = 1;
		break;
	case SUPERMARIO_ST:
		actualState = SUPERMARIO_ST;
		texture = game->getTexture(Game::SUPERMARIO);
		auxscale = 2;
		break;
	default:
		break;
	}
}
