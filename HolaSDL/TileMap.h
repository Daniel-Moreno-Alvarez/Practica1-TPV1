#pragma once
#include <fstream>
#include <vector>
#include <sstream>

#include "Texture.h"
#include "Collision.h"
#include "SceneObject.h"

using namespace std;
class PlayState;

class TileMap : public SceneObject
{
public:
    const int validColums = 4;
    TileMap(PlayState* game, unsigned int _level);
    void render() const override;
    void update() override {};
    virtual SceneObject* clone() const override;

    Collision hit(const SDL_Rect& rect, Collision::Target target) override;
    int getFinalX() const { return final; }
private:
    vector<vector<int>> map;
    int final = -1;
};

