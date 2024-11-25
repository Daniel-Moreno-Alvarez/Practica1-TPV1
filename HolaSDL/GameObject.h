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
	virtual ~GameObject();
	virtual void render() const = 0;
	virtual void updte() = 0;
};

