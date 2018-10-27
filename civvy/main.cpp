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

#include "Civvy.hpp"

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

void end_ncurses() {
    endwin();
}

int main(int argc, const char * argv[]) {
    
    initialize_ncurses();
    GameController::Instance()->run_game();
    end_ncurses();
    
    return 0;
 
}
