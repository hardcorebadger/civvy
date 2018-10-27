//
//  ColorManager.cpp
//  civvy
//
//  Created by Jake Trefethen on 10/26/18.
//  Copyright © 2018 Jake Trefethen. All rights reserved.
//

#include <stdio.h>
#include <ncurses.h>
#include "civvy.hpp"

Icon::Icon(short bg, short fg, char i) {
    col_pair = GameController::Instance()->new_pair(bg,fg);
    icon = i;
}

void Icon::render(const Window& window, Coord c) const {
    wattron(window.get_WINDOW(),COLOR_PAIR(this->col_pair));
    mvwaddch(window.get_WINDOW(), c.y, c.x, this->icon);
    wattroff(window.get_WINDOW(),COLOR_PAIR(this->col_pair));
}

Window::Window() {
    this->window = NULL;
}
Window::Window(int w, int h, int x, int y) {
    width = w; height = h;
    this->window = newwin(h, w, y, x);
    werase(this->window);
    wrefresh(this->window);
}
Window::~Window() {
    werase(this->window);
    wrefresh(this->window);
    delwin(this->window);
}

WINDOW*  Window::get_WINDOW() const {
    return this->window;
}
int Window::get_width() const {
    return this->width;
}
int Window::get_height() const {
    return this->height;
}
