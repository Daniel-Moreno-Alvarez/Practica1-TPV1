#pragma once

class Game;

class GameObject
{
protected:
	Game* game;
public:
	GameObject(Game* _game) : 
		game(_game)
	{};
	virtual ~GameObject() = default;
	virtual void render() const = 0;
	virtual void update() = 0;
};

