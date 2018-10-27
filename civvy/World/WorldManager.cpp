//
//  WorldManager.cpp
//  civvy
//
//  Created by Jake Trefethen on 10/27/18.
//  Copyright © 2018 Jake Trefethen. All rights reserved.
//

#include <stdio.h>
#include "Civvy.hpp"

void WorldManager::initialize_tile_info_map() {
    // https://jonasjacek.github.io/colors/ to check colors
    tile_info_map.insert(std::make_pair(0,TileInfo("Void", 0, Icon(0, 0, ' '))));
    tile_info_map.insert(std::make_pair(1,TileInfo("Sea", 1, Icon(24, 24, ' '))));
    tile_info_map.insert(std::make_pair(2,TileInfo("Plains", 2, Icon(64, 64, ' '))));
    tile_info_map.insert(std::make_pair(3,TileInfo("Beach", 3, Icon(3, 3, ' '))));
    tile_info_map.insert(std::make_pair(4,TileInfo("Pine Forest", 4, Icon(64, 22, '^'))));
    tile_info_map.insert(std::make_pair(5,TileInfo("Ocean", 5, Icon(18, 18, ' '))));
}

TileInfo& WorldManager::get_tile_info(int id) {
    return tile_info_map.at(id);
}
