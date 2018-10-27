//
//  civvy.cpp
//  civvy
//
//  Created by Jake Trefethen on 10/26/18.
//  Copyright © 2018 Jake Trefethen. All rights reserved.
//

#include <iostream>
#include "Civvy.hpp"
#include <string>
#include <unistd.h>

static GameController* gc_inst = NULL;

GameController* GameController::Instance() {
    if (!gc_inst)
        gc_inst = new GameController();
    return gc_inst;
}

GameController::GameController() {
    this->cur_color = 0;
    this->world_mgr = new WorldManager();
    getmaxyx(stdscr, this->window_height, this->window_width);
}

void GameController::run_game() {
    
    // build static maps
    this->world_mgr->initialize_tile_info_map();
    
    // generate world data
    this->world = new World();
    this->world->generate(100, 100);
    
    // build world scene
    this->world_scene = new Scene(this->window_width-25, this->window_height, 0,0);
    this->world_scene->add_object(new WorldView(world_scene, this->world));
    
    // build inpsector scene
    this->inspector_scene = new Scene(25, 5, this->window_width-25, 0);
    this->inspector_scene->add_object(new InspectorView(inspector_scene));

    // main loop
    bool running = true;
    while (running) {
        // render
        this->world_scene->render();
        this->inspector_scene->render();
        
        // wait for input
        int key = getch();
        
        //update logic with input
        switch (key) {
            case 27:
                running = false;
                break;
        }
        this->world_scene->update(key);
        this->inspector_scene->update(key);
        
        // wait a tick
        usleep(14000);
    }
}

int GameController::new_pair(short bg, short fg) {
    this->cur_color++;
    init_pair(this->cur_color, fg, bg);
    return this->cur_color;
}
