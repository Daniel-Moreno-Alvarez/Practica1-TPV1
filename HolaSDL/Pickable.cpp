#include "Pickable.h"
#include "Game.h"
#include "PlayState.h"

Pickable::Pickable(PlayState* _gameST, Point2D _pos) :
	SceneObject(_gameST,_pos)
{
}

Pickable::Pickable(PlayState* _gameST) :
	SceneObject(_gameST)
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
