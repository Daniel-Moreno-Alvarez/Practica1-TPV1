#include "Pickable.h"
#include "Game.h"

Pickable::Pickable(Game* _game, Point2D _pos) : 
	SceneObject(_game,_pos, false)
{
}

Pickable::Pickable(Game* _game) : 
	SceneObject(_game, false)
{
}

void Pickable::render() const
{
	SDL_Rect rect = getRenderRect();
	texture->renderFrame(rect, 0, frame);
}

Collision Pickable::hit(const SDL_Rect& rect, Collision::Target target)
{
	if (target == Collision::PLAYER) {
		return NO_COLLISION;
	}
	Collision coll;
	SDL_Rect actrect = getCollisionRect();
	coll.collides = SDL_IntersectRect(&rect, &actrect, &coll.rect);
	if (coll && target == Collision::ENEMIES) {
		triggerAction();
		delete this;
	}

	return coll;
}
