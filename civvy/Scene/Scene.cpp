//
//  Window.cpp
//  civvy
//
//  Created by Jake Trefethen on 10/27/18.
//  Copyright © 2018 Jake Trefethen. All rights reserved.
//

#include <stdio.h>
#include "Civvy.hpp"

Scene::Scene() {
    this->window = NULL;
}
Scene::Scene(int w, int h, int x, int y) {
    width = w; height = h;
    this->window = newwin(h, w, y, x);
    werase(this->window);
    wrefresh(this->window);
}
Scene::~Scene() {
    werase(this->window);
    wrefresh(this->window);
    delwin(this->window);
}

void Scene::render() const {
    werase(this->window);
    for (int i = 0; i < this->objects.size(); i++) {
        this->objects.at(i)->render();
    }
    wrefresh(this->window);
}

void Scene::update(int key) {
    for (int i = 0; i < this->objects.size(); i++) {
        this->objects.at(i)->update(key);
    }
}

void SceneObject::render() const {
}

void SceneObject::update(int key) {
}
