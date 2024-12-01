#include "Block.h"
#include "Game.h"

Block::Block(Game* _game, std::istream& is) :
	SceneObject(_game, false)
{
	texture = game->getTexture(Game::BLOCKS);
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
	//actualiza el frame para surprise
	if (tipe == SURPRISE) {
		frameTime++;
		if (frameTime >= 5)
		{
			frame++;
			if (frame >= frameMax)
			{
				frame = 0;
			}
			frameTime = 0;
		}
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
	}
	if (coll && coll.rect.y > actrect.y + BlockTam / 4 && coll.rect.w > BlockTam / 4) { // colision por abajo
		if (tipe == SURPRISE || tipe == HIDDEN) {
			tipe = VOID;
			if (action == POWERUP) {
				game->addMushroom(pos);
			}
		}
		if (tipe == BRICK && game->getPlayerState() == SUPERMARIO_ST) {
			isAlive = false;
		}
	}
	return coll;
}

SceneObject* Block::clone() const
{
	return new Block(*this);
}
