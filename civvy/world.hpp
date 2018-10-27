//
//  world.hpp
//  civvy
//
//  Created by Jake Trefethen on 10/26/18.
//  Copyright © 2018 Jake Trefethen. All rights reserved.
//

#ifndef world_hpp
#define world_hpp

#include <stdio.h>
#include <map>
#include <ncurses.h>
#include "civvy.hpp"

struct Tile;
class TileInfo;
struct Coord;
class World;

class World {
private:
    std::map<Coord, Tile> tiles;
    int width,height;
public:
    void generate(int w, int h);
    void render(const WINDOW * win);
};

struct Coord {
    int x;
    int y;
};

struct Tile {
    Coord pos;
    int id;
};

class TileInfo {
private:
    int id;
    Icon icon;
public:
    TileInfo(int i, Icon ic) {
        id = i; icon=ic;
    }
    static std::map<int, TileInfo> tile_info_map;
};

#endif /* world_hpp */
