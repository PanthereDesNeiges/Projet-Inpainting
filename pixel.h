#pragma once
#include <Imagine/Graphics.h>
using namespace Imagine;

class pixel {
    int x,y;     // position
    Color col;      // Color
    double c,d;     // Confidence and Data term
    bool v;         // 0 if not visited yet, 1 else

public:
    int getX();
    int getY();
    Color getColor();
    double getConfidence();
    double getData();
    double getPriority();
    bool getV();

    void setPixel(int x1, int y1, Color col1, double c1, double d1, bool v1);
    void setBlanck(int x1, int y1);    // To initialize the pixels in the target zone
};


