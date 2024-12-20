#include "Block.h"
#include "Game.h"
#include "checkML.h"

Block::Block(PlayState* _gameST, std::istream& is) :
	SceneObject(_gameST)
{
	texture = playST->getGame()->getTexture(Game::BLOCKS);
	char _tipe;
	is >> pos >> _tipe;
	pos = pos * BlockTam;
	height = BlockTam;
	width = BlockTam;

	char _action = ' ';

	switch (_tipe)
	{
	case 'B':
		tipe = BRICK;
		break;
	case '?':
		tipe = SURPRISE;
		is >> _action;
		break;
	case 'H':
		tipe = HIDDEN;
		is >> _action;
		break;
	default:
		tipe = VOID;
		break;
	}

	switch (_action)
	{
	case 'P':
		action = POWERUP;
		break;
	case 'C':
		action = COIN;
		break;
	default:
		action = NONE;
		break;
	}
}

void Block::render() const
{
	SDL_Rect rect = getRenderRect();

	switch (tipe)
	{
	case BRICK:
		texture->renderFrame(rect, 0, 5);
		break;
	case SURPRISE:
		texture->renderFrame(rect, 0, frame);
		break;
	case VOID:
		texture->renderFrame(rect, 0, 4);
		break;
	case HIDDEN:
		break;
	default:
		break;
	}
}

void Block::update()
{
	// Actualiza el frame para surprise
	if (tipe == SURPRISE) {
		frame = (playST->getFrames() / ANIM_RANGE) % frameMax;
	}
}

Collision Block::hit(const SDL_Rect& rect, Collision::Target target) {
	Collision coll;
	SDL_Rect actrect = getCollisionRect();
	coll.collides = SDL_IntersectRect(&rect, &actrect, &coll.rect);
	if (coll)
	{
		coll.horizontal = coll.rect.w;
		coll.vertical = coll.rect.h;
		coll.result = Collision::OBSTACLE;
	}
	if (coll && coll.rect.y > actrect.y + BlockTam4 && coll.rect.w > BlockTam4) { // colision por abajo
		if (tipe == SURPRISE || tipe == HIDDEN) {
			tipe = VOID;
			if (action == POWERUP) {
				playST->addMushroom(Point2D(pos.getX(), pos.getY() - BlockTam));
			}
			else if (action == COIN) {
				playST->addPoints(coinPoints);
			}
		}
		else if (tipe == BRICK && playST->getPlayerState() == SUPERMARIO_ST) {
			playST->addPoints(brickPoints);
			delete this;
		}
	}
	return coll;
}

SceneObject* Block::clone() const
{
	return new Block(*this);
}
