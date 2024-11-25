#pragma once
#include <SDL.h>
struct Collision {
	bool collides = false;
	bool damages = false;
	bool isEnemy = false;
	SDL_Rect rect;

	operator bool() const { return collides; }

	// ¿A quién afecta esta colisión? Se puede usar en lugar del
	// bool fromPlayer para objetos que atacan tanto a enemigos
	// como al jugador (caparaszón opciona).
	enum Target {
		ENEMIES = 1,	// afecta a enemigos
		PLAYER = 2,	// afecta al jugador
		BOTH = 3,	// afecta a ambos
	};

	// Tipo de resultado de la colisión
	enum Result {
		NONE,		// no ha habido colisión
		DAMAGE,		// la colisión produce daño
		OBSTACLE,	// la colisión impide el movimiento
	};

	Result result = NONE;
	int horizontal = 0;   // profundidad de la colisión horizontal
	int vertical = 0;     // profundidad de la colisión vertical
};