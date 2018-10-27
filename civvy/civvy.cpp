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
    tile_info_map.insert(std::make_pair(0,TileInfo("Void", 0, Icon(0, 0, ' '))));
    tile_info_map.insert(std::make_pair(1,TileInfo("Sea", 1, Icon(24, 24, ' '))));
    tile_info_map.insert(std::make_pair(2,TileInfo("Plains", 2, Icon(64, 64, ' '))));
    tile_info_map.insert(std::make_pair(3,TileInfo("Beach", 3, Icon(3, 3, ' '))));
    tile_info_map.insert(std::make_pair(4,TileInfo("Pine Forest", 4, Icon(64, 22, '^'))));
    tile_info_map.insert(std::make_pair(5,TileInfo("Ocean", 5, Icon(18, 18, ' '))));

}

int GameController::new_pair(short bg, short fg) {
    this->cur_color++;
    init_pair(this->cur_color, fg, bg);
    return this->cur_color;
}

TileInfo GameController::get_tile_info(int id) {
    return tile_info_map.at(id);
}

WorldView::WorldView() {
    cursor = {COLOR_WHITE, COLOR_BLACK, '+'};
}

void WorldView::render(const Window& window, const World& world) const {
    world.render(window, this->base_pos);
    cursor.render(window, this->world_to_view(this->curs_pos));
}

void WorldView::update(const Window& window, const World& world, int key) {
    switch (key) {
        case KEY_RIGHT:
            this->curs_pos.x++;
            break;
        case KEY_LEFT:
            this->curs_pos.x--;
            break;
        case KEY_UP:
            this->curs_pos.y--;
            break;
        case KEY_DOWN:
            this->curs_pos.y++;
            break;
    }
    Coord c = world_to_view(this->curs_pos);
    if (c.x < 0)
        this->base_pos.x--;
    if (c.x >= window.get_width())
        this->base_pos.x++;
    if (c.y < 0)
        this->base_pos.y--;
    if (c.y >= window.get_height())
        this->base_pos.y++;
}

Coord WorldView::get_base_pos() const {
    return this->base_pos;
}

Coord WorldView::get_curs_pos() const {
    return this->curs_pos;
}

Coord WorldView::world_to_view(Coord c) const {
    return c - base_pos;
}
