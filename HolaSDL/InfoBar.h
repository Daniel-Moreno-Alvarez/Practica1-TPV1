#pragma once
#include "GameObject.h"
#include "Texture.h"

class InfoBar : public GameObject
{
private:
	Texture* numeros;
	int tam = 20;
	int offset = 5;
	int points = 0;
public:
	InfoBar(Game* _game);

	void render() const override;
	void update() override {};

	void setPoints(int _p) { points += _p; };
};