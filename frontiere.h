#pragma once
#include <Imagine/Graphics.h>
using namespace Imagine;

#include "image.h"

class frontiere {
    pixel *f;
public:
    void add_frontiere();
    void initialize_frontiere();
    void pop_frontiere();
    pixel max_priority();
};
