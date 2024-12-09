#pragma once

class GameState;

class GameObject
{
protected:
	GameState* gameST;
public:
	explicit GameObject(GameState* _gameST) :
		gameST(_gameST)
	{};
	virtual ~GameObject() = default;
	virtual void render() const = 0;
	virtual void update() = 0;
};

