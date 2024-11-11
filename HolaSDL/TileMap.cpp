#include "TileMap.h"
#include "Game.h"

TileMap::TileMap(Game* _game) : game(_game), texture(game->getTexture(Game::BACKGROUND)){

    ifstream file(game->getMap(Game::WORLD1CSV));
    string line;

    while (getline(file, line)) {
        vector<int> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ',')) {
            row.push_back(stoi(cell));  //Convierte cada valor a entero y lo mete en la fila
        }
        map.push_back(row);  // mete la fila al mapa
    }
    file.close();
}

void TileMap::render() const
{
    int ini = game->getMapOffset() / BlockTam;
    int fin = ini + Game::WIN_WIDTH / BlockTam + 1;
    for (size_t i = 0; i < map.size(); i++)
    {
        for (size_t j = ini; j < fin; j++)
        {
            SDL_Rect rect{ j * BlockTam - game->getMapOffset(), i * BlockTam, BlockTam, BlockTam };
            int x = 0, y = 0;
            int indice = map[i][j];
            if (indice > 0) {
                x = indice / texture->getNumColumns();
                y = indice % texture->getNumColumns();
            }
            texture->renderFrame(rect, x, y);
        }
    }
}

Collision TileMap::hit(const SDL_Rect& rect, bool fromPlayer) {
    Collision coll;

    int ini = game->getMapOffset() / BlockTam;
    int fin = ini + Game::WIN_WIDTH / BlockTam + 5;
    for (int i = 0; i < map.size() && !coll; i++) {
        for (int j = ini; j < fin && !coll; j++) {
            if (map[i][j] > 0 && map[i][j] % texture->getNumColumns() < 4) {
                SDL_Rect actrect{ j * BlockTam, i * BlockTam, BlockTam, BlockTam };
                coll.collides = SDL_IntersectRect(&rect, &actrect, &coll.rect);
                if (coll) {
                    coll.collides = true;
                }
            }
        }
    }

    return coll;
}