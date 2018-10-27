//
//  world.cpp
//  civvy
//
//  Created by Jake Trefethen on 10/26/18.
//  Copyright © 2018 Jake Trefethen. All rights reserved.
//

#include <map>
#include <cstdlib>
#include <ncurses.h>
#include <iostream>

#include "Civvy.hpp"
#include "PerlinNoise.hpp"

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
    width = w;
    height = h;
    double pscale = 0.07f;
    const PerlinNoise perlin(2743.328f);
    tiles = new Tile*[w];
    for (int x = 0; x < w; x++) {
        tiles[x] = new Tile[h];
        for (int y = 0; y < h; y++) {
            Coord c{x,y};
            double d = perlin.noise(pscale*x, pscale*y);
            int id = 5;
            if (d > -0.33)
                id = 1;
            if (d > -0.1)
                id = 3;
            if (d > 0.0)
                id = 2;
            if (d > 0.3 && (rand()%2) == 0)
                id = 4;
            if (d > 0.5)
                id = 4;
            tiles[x][y] = Tile{c,id};
        }
    }
}

void World::render(const Scene* scene, Coord base_pos) const {
    for (int x = base_pos.x; x < scene->get_width()+base_pos.x; x++) {
        for (int y = base_pos.y; y < scene->get_height()+base_pos.y; y++) {
            Coord c{x,y};
            if (!this->in_world(c))
                continue;
            GameController::Instance()->get_world_manager()->get_tile_info(this->tiles[x][y].id).render(scene, c-base_pos);
        }
    }
}

bool World::in_world(Coord c) const {
    if (c.x < 0 || c.y < 0 || c.x >= width || c.y >= height)
        return false;
    return true;
}

Tile World::get_tile(Coord c) {
    if (!this->in_world(c))
        return Tile{c,0};
    return this->tiles[c.x][c.y];
}
