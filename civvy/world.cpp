//
//  world.cpp
//  civvy
//
//  Created by Jake Trefethen on 10/26/18.
//  Copyright © 2018 Jake Trefethen. All rights reserved.
//

#include "civvy.hpp"
#include <map>
#include <cstdlib>
#include <ncurses.h>
#include <iostream>

World::World() {}


World::~World() {
    if (tiles == NULL)
        return;
    for (int x = 0; x < width; x++) {
        delete[] tiles[x];
    }
    delete[] tiles;
}

void World::generate(int w, int h) {
    tiles = new Tile*[w];
    for (int x = 0; x < w; x++) {
        tiles[x] = new Tile[h];
        for (int y = 0; y < h; y++) {
            Coord c{x,y};
            int id = 1 + (rand() % 2);
            tiles[x][y] = Tile{c,id};
        }
    }
}

void World::render(const Window& window) const {
    for (int x = 0; x < window.get_width(); x++) {
        for (int y = 0; y < window.get_height(); y++) {
            Coord c{x,y};
            GameController::Instance()->get_tile_info(this->tiles[x][y].id).render(window, c);
        }
    }
}

Tile World::get_tile(Coord c) {
    return this->tiles[c.x][c.y];
}

TileInfo World::get_tile_info(Coord c) {
    return GameController::Instance()->get_tile_info(this->get_tile(c).id);
}

void TileInfo::render(const Window& window, Coord c) const {
    this->icon.render(window, c);
}

std::string TileInfo::get_name() const {
    return this->name;
}

bool operator== (const Coord &c1, const Coord &c2) {
    return c1.x == c2.x && c1.y == c2.y;
}
bool operator!= (const Coord &c1, const Coord &c2) {
    return !(c1==c2);
}
bool operator< (const Coord &c1, const Coord &c2) {
    return c1.x+c1.y < c2.x+c2.y;
}
