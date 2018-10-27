//
//  ColorManager.cpp
//  civvy
//
//  Created by Jake Trefethen on 10/26/18.
//  Copyright © 2018 Jake Trefethen. All rights reserved.
//

#include <stdio.h>
#include <ncurses.h>
#include "Civvy.hpp"

Icon::Icon(short bg, short fg, char i) {
    col_pair = GameController::Instance()->new_pair(bg,fg);
    icon = i;
}

void Icon::render(const Scene* scene, Coord c) const {
    wattron(scene->get_Window(),COLOR_PAIR(this->col_pair));
    mvwaddch(scene->get_Window(), c.y, c.x, this->icon);
    wattroff(scene->get_Window(),COLOR_PAIR(this->col_pair));
}
