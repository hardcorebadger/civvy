//
//  WorldView.cpp
//  civvy
//
//  Created by Jake Trefethen on 10/27/18.
//  Copyright © 2018 Jake Trefethen. All rights reserved.
//

#include <stdio.h>
#include "Civvy.hpp"

void WorldView::render() const {
    SceneObject::render();
    this->world->render(this->scene, this->base_pos);
    cursor.render(this->scene, this->world_to_view(this->curs_pos));
}

void WorldView::update(int key) {
    SceneObject::update(key);
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
    if (c.x >= this->scene->get_width())
        this->base_pos.x++;
    if (c.y < 0)
        this->base_pos.y--;
    if (c.y >= this->scene->get_height())
        this->base_pos.y++;
    
    GameController::Instance()->set_current_pos(curs_pos);
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
