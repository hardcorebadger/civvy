//
//  InspectorView.cpp
//  civvy
//
//  Created by Jake Trefethen on 10/27/18.
//  Copyright © 2018 Jake Trefethen. All rights reserved.
//

#include <stdio.h>

#include "Civvy.hpp"

void InspectorView::render() const {
    SceneObject::render();
    wborder(this->scene->get_Window(), '|', '|', '-', '-', '+', '+', '+', '+');
    Coord cp = GameController::Instance()->get_current_pos();
    std::string s = GameController::Instance()->get_world()->get_tile_info(cp).get_name();
    mvwprintw(this->scene->get_Window(),1,1,"(%d,%d): %s", cp.x, cp.y, s.c_str());
}

void InspectorView::update(int key) {
    SceneObject::update(key);
}
