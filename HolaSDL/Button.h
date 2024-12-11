#pragma once
#include <functional>
#include "GameObject.h"
#include "EventHandler.h"
#include "Texture.h"
#include "Vector2D.h"
#include "gameState.h"

using Callback = std::function<void(void)>;

class Button : public GameObject, public EventHandler
{
public:
	Button(GameState* gameState, Texture* _texture, Point2D pos);

	void render() const override;
	void update() override;

	void handleEvent(const SDL_Event& event) override;

	void connect(const Callback& c);

private:
	Point2D pos;
	Texture* texture;
	SDL_Rect rect;
	Texture* mushTexture;
	SDL_Rect mushRect;

	int buttonST;
	enum buttonState {
		DEFAULT = 0,
		OVER = 1, // cuando el raton este sobre el rect
		CLICK = 2 // cuando el raton haga click
	};

	std::list<Callback> callbacks;

	SDL_Point mouse; // ubicación del ratón

	void emit() const;

	SDL_Color yellow = {255, 255, 0, 255};
};