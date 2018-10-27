//
//  main.cpp
//  civvy
//
//  Created by Jake Trefethen on 10/26/18.
//  Copyright © 2018 Jake Trefethen. All rights reserved.
//

#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include "civvy.hpp"

void initialize_ncurses() {
    initscr();
    curs_set(0);
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    
    if(has_colors() == FALSE)
    {    endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
}

int main(int argc, const char * argv[]) {
    
    initialize_ncurses();
    GameController::Instance()->initialize_tile_info_map();
    
    Icon cursor{COLOR_WHITE, COLOR_BLACK, '+'};

    World w;
    w.generate(100, 100);
    
    WorldView wv;

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    Window world_window(max_x-20, max_y, 0,0);
    Window inspector_window(20, 5, max_x-20, 0);

    bool running = true;
    while (running) {
        werase(world_window.get_WINDOW());
        wv.render(world_window, w);
        wrefresh(world_window.get_WINDOW());

        werase(inspector_window.get_WINDOW());
        wborder(inspector_window.get_WINDOW(), '|', '|', '-', '-', '+', '+', '+', '+');
        Coord cp = wv.get_curs_pos();
        Coord bp = wv.get_base_pos();
        std::string s = w.get_tile_info(cp).get_name();
        mvwprintw(inspector_window.get_WINDOW(),1,1,"(%d,%d): %s", cp.x, cp.y, s.c_str());
        wrefresh(inspector_window.get_WINDOW());
        int key = getch();
        switch (key) {
            case 27:
                running = false;
                break;
        }
        wv.update(world_window, w, key);
        usleep(14000);
    }
    endwin();
    return 0;
}
