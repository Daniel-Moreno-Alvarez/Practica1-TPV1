#pragma once

#include <array>

// Biblioteca SDL
#include <SDL.h>
#include "GameList.h"
#include "Texture.h"
#include "TileMap.h"
#include "Player.h"
#include "Block.h"
#include "Collision.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Mushroom.h"
#include "SceneObject.h"

using uint = unsigned int;

const float SCALE = 2;
const float BlockTam = 32;
const float BlockTam2 = BlockTam / 2;
const float BlockTam4 = BlockTam / 4;
const Point2D gravity = Point2D(0, 2);
//
// Clase que representa el juego y controla todos sus aspectos
//
class Game
{
public:
	// Identificadores de las texturas
	enum TextureName {
		BACKGROUND,
		BLOCKS,
		FIREMARIO,
		GOOMBA,
		KOOPA,
		MARIO,
		MUSHROOM,
		PIRANHA,
		PLANT,
		SHELL,
		STAR,
		SUPERMARIO,
		NUM_TEXTURES,  // Truco C++: número de texturas definidas
	};

	// Identificadores de las texturas
	enum MapName {
		WORLD1CSV,
		WORLD1TXT,
		NUM_MAPS,  // Truco C++: número de texturas definidas
	};

private:
	// Ventana de la SDL (se destruirá en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;
	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> textures;
	// Array con todas los maps de juego csv y txt
	std::array<std::string, NUM_MAPS> maps;
	// Interruptor para terminar el juego
	bool seguir;
	//offset del mapa
	int mapOffset = 0;
	// Objetos del juego
	TileMap* level;
	Player* player;
	vector<Block*>* blocks;
	vector<Goomba*>* goombas;
	vector<Koopa*>* koopas;
	vector<Mushroom*>* mushrooms;

	int finalX;

public:
	void run();

	void update();
	void render();
	void handleEvents();
	void loadMap();
	Collision checkCollision(const SDL_Rect& rect, bool fromPlayer);
	void addMushroom(Point2D _pos);
	void renderLifes();

	// Constante globales
	static constexpr uint WIN_WIDTH = 576;
	static constexpr uint WIN_HEIGHT = 512;
	static constexpr uint FRAME_RATE = 50;

	// Geters
	int getMapOffset() const { return mapOffset; };
	PlayerState getPlayerState() { return player->getState(); }
	Texture* getTexture(TextureName name) const;
	string getMap(MapName name) const;

	// Seters
	void setPlayerState(PlayerState pySt) { player->SetState(pySt); }

	Game();
	~Game();
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

inline string
Game::getMap(MapName name) const {
	return maps[name];
}
