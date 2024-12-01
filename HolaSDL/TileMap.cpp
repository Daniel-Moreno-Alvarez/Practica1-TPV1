#include "TileMap.h"
#include "Game.h"

TileMap::TileMap(Game* _game, unsigned int _level) : game(_game), level(_level) {
    try {
        texture = game->getTexture(Game::BACKGROUND);

        string i = to_string(level);
        ifstream file("../assets/maps/world" + i + ".csv");
        string line;

        while (getline(file, line)) {
            vector<int> row;
            stringstream ss(line);
            string cell;
            int i = 0; // contador para encontrar el final
            while (getline(ss, cell, ',')) {
                row.push_back(stoi(cell));  //Convierte cada valor a entero y lo mete en la fila
                if (final == -1 && stoi(cell) == 34) // si encuntra la bandera que guarde su posicion en el eje x
                {
                    final = i;
                }
                else { i++; }
            }
            map.push_back(row);  // mete la fila al mapa
        }
        file.close();
    }
	catch (const std::string& error)
	{
		throw "Error al cargar " + game->getMap(Game::WORLD1CSV);
	}
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
    int fin = ini + Game::WIN_WIDTH / BlockTam + 1;
    for (int i = 0; i < map.size() && !coll; i++) {
        for (int j = ini; j < fin && !coll; j++) {
            if (map[i][j] > 0 && map[i][j] % texture->getNumColumns() < validColums) {
                SDL_Rect actrect{ j * BlockTam, i * BlockTam, BlockTam, BlockTam };
                if (SDL_HasIntersection(&rect, &actrect)) {
                    SDL_Rect intersection;
                    if (SDL_IntersectRect(&rect, &actrect, &intersection)) {
                        coll.rect = intersection;
                        coll.collides = true;
                        coll.horizontal = intersection.w;
                        coll.vertical = intersection.h;
                        return coll;
                    }
                }
            }
        }
    }

    return coll;
}