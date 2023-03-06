#pragma once
#include <Imagine/Graphics.h>
using namespace Imagine;

#include "image.h"

class frontiere {
    std::list<pixel> f;
public:
    void add_frontiere(pixel p);
    void initialize_frontiere(std::vector<pixel> v);   // prend en argument la liste de points à partir de laquelle on fait la frontière
    void pop_frontiere();
    pixel max_priority();
};
