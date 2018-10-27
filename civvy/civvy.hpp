//
//  civvy.hpp
//  civvy
//
//  Created by Jake Trefethen on 10/26/18.
//  Copyright © 2018 Jake Trefethen. All rights reserved.
//

#ifndef civvy_h
#define civvy_h

#include <map>
#include "ncurses.h"
#include <string>

struct Tile;
class TileInfo;
struct Coord;
class World;
struct Icon;
class Window;
class RenderManager;
class GameController;
class WorldView;

struct Icon {
    int col_pair;
    char icon;
    Icon(){}
    Icon(short bg, short fg, char i);
    void render(const Window& window, Coord c) const;
};

class Window {
private:
    WINDOW * window;
    int width;
    int height;
public:
    Window();
    Window(int w, int h, int x, int y);
    ~Window();
    WINDOW* get_WINDOW() const;
    int get_width() const;
    int get_height() const;
};

class World {
private:
    Tile** tiles;
    int width,height;
    Window* window;
public:
    World();
    ~World();
    void generate(int w, int h);
    void render(const Window& window, Coord base_pos) const;
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
    void render(const Window& window, Coord c) const;
    std::string get_name() const;
};

class WorldView {
public:
    WorldView();
    void render(const Window& window, const World& world) const;
    void update(const Window& window, const World& world, int key);
    Coord get_base_pos() const;
    Coord get_curs_pos() const;
    Coord world_to_view(Coord c) const;
private:
    Coord base_pos;
    Coord curs_pos;
    Icon cursor;
};

class GameController {
public:
    GameController();
    static GameController* Instance();
    int new_pair(short bg, short fg);
    TileInfo get_tile_info(int id);
    void initialize_tile_info_map();
private:
    int cur_color;
    std::map<int, TileInfo> tile_info_map;
};

#endif /* civvy_h */
