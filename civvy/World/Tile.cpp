//
//  Tile.cpp
//  civvy
//
//  Created by Jake Trefethen on 10/27/18.
//  Copyright © 2018 Jake Trefethen. All rights reserved.
//

#include "Civvy.hpp"

TileInfo World::get_tile_info(Coord c) {
    return GameController::Instance()->get_world_manager()->get_tile_info(this->get_tile(c).id);
}

void TileInfo::render(const Scene* scene, Coord c) const {
    this->icon.render(scene, c);
}

std::string TileInfo::get_name() const {
    return this->name;
}
