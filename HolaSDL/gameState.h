#pragma once
#include <SDL.h>
#include <list>
#include "GameObject.h"
#include "EventHandler.h"
#include "GameList.h"

class Game;

class GameState {
public:
	GameState(Game* _game) : game(_game){};
	GameState(const GameState& other) :
		game(other.game),
		eventHandlers(other.eventHandlers)
	{};
	virtual void render() const = 0;
	virtual void update() = 0;
	virtual void handleEvent(const SDL_Event& event);
	virtual ~GameState();
	virtual void onEnter() {};
	Game* getGame() const { return game; };
protected:
	Game* game;
	GameList<GameObject> gameObjects;
	std::list<EventHandler*> eventHandlers;
};


