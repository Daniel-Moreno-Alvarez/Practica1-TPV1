#pragma once
#include "Pickable.h"
#include <istream>
class Game;

class Coin : public Pickable
{
private:
	int frameMax = 4;
public:
	Coin(Game* _game, std::istream& is);

	void update() override;
	void triggerAction() override;

	SceneObject* clone() const override;
};

