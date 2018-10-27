//
//  civvy.hpp
//  civvy
//
//  Created by Jake Trefethen on 10/26/18.
//  Copyright © 2018 Jake Trefethen. All rights reserved.
//

#ifndef Civvy_hpp
#define Civvy_hpp

#include <map>
#include "ncurses.h"
#include <string>
#include <vector>

struct Tile;
class TileInfo;
struct Coord;
class World;
struct Icon;
class Scene;
class RenderManager;
class GameController;
class WorldView;
class WorldManager;
class SceneObject;

struct Icon {
    int col_pair;
    char icon;
    Icon(){}
    Icon(short bg, short fg, char i);
    void render(const Scene* scene, Coord c) const;
};

class Scene {
private:
    WINDOW * window;
    int width;
    int height;
    std::vector<SceneObject*> objects;
public:
    Scene();
    Scene(int w, int h, int x, int y);
    ~Scene();
    WINDOW* get_Window() const { return window;}
    int get_width() const { return width;}
    int get_height() const { return height;}
    virtual void render() const;
    virtual void update(int key);
    virtual void add_object(SceneObject* o) { objects.push_back(o);}
};

class SceneObject {
protected:
    Scene* scene;
public:
    SceneObject(Scene* s) : scene(s) {}
    virtual void render() const;
    virtual void update(int key);
};

class World {
private:
    Tile** tiles;
    int width,height;
public:
    World();
    ~World();
    void generate(int w, int h);
    void render(const Scene* scene, Coord base_pos) const;
    Tile get_tile(Coord c);
    TileInfo get_tile_info(Coord c);
    bool in_world(Coord c) const;
};

struct Coord {
    int x;
    int y;
    friend bool operator== (const Coord &c1, const Coord &c2);
    friend bool operator!= (const Coord &c1, const Coord &c2);
    Coord operator+(const Coord& v) const;
    Coord operator-(const Coord& v) const;
};

struct Tile {
    Coord pos;
    int id;
};

class TileInfo {
private:
    int id;
    Icon icon;
    std::string name;
public:
    TileInfo(const std::string& s, int i, Icon ic) : name(s), id(i) {
        icon=ic;
    }
    void render(const Scene* scene, Coord c) const;
    std::string get_name() const;
};

class WorldManager {
public:
    WorldManager(){}
    TileInfo& get_tile_info(int id);
    void initialize_tile_info_map();
private:
    std::map<int, TileInfo> tile_info_map;
};

class GameController {
public:
    GameController();
    static GameController* Instance();
    int new_pair(short bg, short fg);
    WorldManager* get_world_manager() const {return world_mgr;}
    void run_game();
    int get_window_width() const {return window_width;}
    int get_window_height() const {return window_height;}
    Coord get_current_pos() const { return current_pos;}
    void set_current_pos(Coord c) { current_pos = c;}
    World* get_world() const {return world;}
    Scene* get_world_scene() const {return world_scene;}
    Scene* get_inspector_scene() const {return inspector_scene;}
private:
    int cur_color;
    int window_width, window_height;
    Coord current_pos;
    World* world;
    WorldManager* world_mgr;
    Scene* world_scene;
    Scene* inspector_scene;
};

class WorldView : public SceneObject {
public:
    WorldView(Scene* s, World* w) : SceneObject(s), world(w) {cursor = {COLOR_WHITE, COLOR_BLACK, '+'};}
    void render() const;
    void update(int key);
    Coord get_base_pos() const;
    Coord get_curs_pos() const;
    Coord world_to_view(Coord c) const;
private:
    World* world;
    Coord base_pos;
    Coord curs_pos;
    Icon cursor;
};

class InspectorView : public SceneObject {
public:
    InspectorView(Scene* s) : SceneObject(s) {}
    void render() const;
    void update(int key);
private:

};

#endif /* civvy_hpp */
