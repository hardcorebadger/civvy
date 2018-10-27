//
//  civvy.cpp
//  civvy
//
//  Created by Jake Trefethen on 10/26/18.
//  Copyright © 2018 Jake Trefethen. All rights reserved.
//

#include <iostream>
#include "civvy.hpp"
#include <string>

static GameController* gc_inst = NULL;

GameController* GameController::Instance() {
   if (!gc_inst)
       gc_inst = new GameController();
    return gc_inst;
}

GameController::GameController() {
    this->cur_color = 0;
}

void GameController::initialize_tile_info_map() {
    // https://jonasjacek.github.io/colors/ to check colors
    tile_info_map.insert(std::make_pair(1,TileInfo("Ocean", 1, Icon(24, 24, ' '))));
    tile_info_map.insert(std::make_pair(2,TileInfo("Plains", 2, Icon(106, 106, ' '))));
    tile_info_map.insert(std::make_pair(3,TileInfo("Sand", 3, Icon(3, 3, ' '))));
}

int GameController::new_pair(short bg, short fg) {
    this->cur_color++;
    init_pair(this->cur_color, fg, bg);
    return this->cur_color;
}

TileInfo GameController::get_tile_info(int id) {
    return tile_info_map.at(id);
}
