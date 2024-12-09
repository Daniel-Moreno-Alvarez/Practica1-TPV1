#pragma once
#include <SDL.h>
#include <list>
#include "GameObject.h"
#include "EventHandler.h"

class Game;

class GameState {
public:
	GameState(Game* _game) : game(_game){};
	GameState(const GameState& other) :
		game(other.game),
		gameObjects(other.gameObjects),
		eventHandlers(other.eventHandlers)
	{};
	virtual void render() const;
	virtual void update() = 0;
	virtual void handleEvent(const SDL_Event& event);
	virtual ~GameState() = default;
	virtual void onEnter() {};
	Game* getGame() const { return game; };
protected:
	Game* game;
	std::list<GameObject*> gameObjects;
	std::list<EventHandler*> eventHandlers;
};


