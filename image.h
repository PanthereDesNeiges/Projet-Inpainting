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
    pixel getPixel(int x, int y);
    void setPixel(int x, int y, pixel p);
    void CopyPaste(int xd, int yd, int wd, int hd, int xa, int ya);  //d comme départ, a comme arrivée


};

int translatation(int x, int y, int xd, int yd, int xa, int ya);
