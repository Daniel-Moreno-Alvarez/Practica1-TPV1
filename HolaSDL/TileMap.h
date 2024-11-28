#pragma once
#include <fstream>
#include <vector>
#include <sstream>

#include "Texture.h"
#include "Collision.h"

using namespace std;
class Game;


class TileMap {
    Game* game;
    Texture* texture;
public:
    const int validColums = 4;
    TileMap(Game* game);
    void render() const;
    Collision hit(const SDL_Rect& rect, bool fromPlayer);
    int getFinalX() const { return final; }
private:
    vector<vector<int>> map;
    int final = -1;
};

