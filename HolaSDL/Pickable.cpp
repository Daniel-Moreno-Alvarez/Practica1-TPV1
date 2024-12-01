#include "Pickable.h"
#include "Game.h"

Pickable::Pickable(Game* _game, Point2D _pos) : 
	SceneObject(_game,_pos, false)
{
}

void Pickable::render() const
{
	SDL_Rect rect = getRenderRect();
	texture->renderFrame(rect, 0, 0);
}

Collision Pickable::hit(const SDL_Rect& rect, Collision::Target target)
{
	Collision coll;
	SDL_Rect actrect = getCollisionRect();
	coll.collides = SDL_IntersectRect(&rect, &actrect, &coll.rect);
	if (coll && target == Collision::ENEMIES) {
		isAlive = false;

		triggerAction();
	}

	return coll;
}
