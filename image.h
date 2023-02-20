#pragma once
#include <Imagine/Graphics.h>
using namespace Imagine;
#include "pixel.h"

class image {
    int w,h;
    pixel *data; // pointeur vers le tableau de pixels

public:
    image(int width, int height); // Constructeur
    ~image(); // Destructeur
    int getW();
    int getH();
    pixel getData(int x, int y);
    void setPixel(int x, int y, pixel p);
};

