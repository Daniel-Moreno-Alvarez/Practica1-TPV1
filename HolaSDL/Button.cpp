#include "checkML.h"
#include "Game.h"
#include "Button.h"

Button::Button(GameState* _gameST, Texture* _texture, Point2D _pos)
	: GameObject(_gameST),texture(_texture), pos(_pos)
{
	buttonST = DEFAULT;

	mushTexture = gameST->getGame()->getTexture(Game::MUSHROOM);
	mouse.x = 0;
	mouse.y = 0;

	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
	rect.x = int(pos.getX()) - rect.w / 2;
	rect.y = int(pos.getY()) - rect.h / 2;

	mushRect.x = rect.x - BlockTam;
	mushRect.y = rect.y;
	mushRect.w = rect.h;
	mushRect.h = rect.h;
}

void Button::emit() const
{
	for (Callback callback : callbacks) {
		callback();
	}
}

void Button::render() const
{
	if (buttonST == OVER)
	{
		mushTexture->render(mushRect);
		texture->render(rect, yellow);
	}
	else texture->render(rect);
}

void Button::update()
{
	SDL_GetMouseState(&mouse.x, &mouse.y);

	if (SDL_PointInRect(&mouse, &rect)) {
		buttonST = OVER;
	}
	else buttonST = DEFAULT;
}

void Button::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
	{
		// pos del cursor al pulsar
		mouse.x = event.button.x;
		mouse.y = event.button.y;

		// si el punto esta en el rect del boton
		if (SDL_PointInRect(&mouse, &rect))
		{
			buttonST = CLICK;
			emit();
		}
	}
}

void Button::connect(const Callback& callback)
{
	callbacks.push_back(callback);
}