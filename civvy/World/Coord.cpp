//
//  Coord.cpp
//  civvy
//
//  Created by Jake Trefethen on 10/27/18.
//  Copyright © 2018 Jake Trefethen. All rights reserved.
//

#include <stdio.h>
#include "Civvy.hpp"

bool operator== (const Coord &c1, const Coord &c2) {
    return c1.x == c2.x && c1.y == c2.y;
}
bool operator!= (const Coord &c1, const Coord &c2) {
    return !(c1==c2);
}
Coord Coord::operator+(const Coord& v) const {
    return Coord{this->x+v.x, this->y+v.y};
}
Coord Coord::operator-(const Coord& v) const {
    return Coord{this->x-v.x, this->y-v.y};
}
