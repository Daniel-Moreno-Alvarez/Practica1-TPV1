#include "Lift.h"
#include "Game.h"
Lift::Lift(Game* _game, std::istream& is) :
	SceneObject(_game)
{
	texture = game->getTexture(Game::LIFT);
	height = texture->getFrameHeight();
	width = texture->getFrameWidth();
	int speed;
	is >> pos >> speed;
	pos = pos * BlockTam;
	vel.setY(speed);
}

void Lift::render() const
{
	SDL_Rect rect = getRenderRect();
	texture->renderFrame(rect, 0, 0);
}

void Lift::update()
{
	pos = pos + vel;
	if (pos.getY() > Game::WIN_HEIGHT) {
		pos.setY(0);
	}
	if (pos.getY() < 0) {
		pos.setY(Game::WIN_HEIGHT);
	}
}

Collision Lift::hit(const SDL_Rect& rect, Collision::Target target)
{
	Collision coll;
	SDL_Rect actrect = getCollisionRect();
	coll.collides = SDL_IntersectRect(&rect, &actrect, &coll.rect);
	if (coll)
	{
		coll.horizontal = coll.rect.w;
		coll.vertical = coll.rect.h;
		coll.result = Collision::OBSTACLE;
		return coll;
	}
	return NO_COLLISION;
}

SceneObject* Lift::clone() const
{
	return new Lift(*this);
}
