#pragma once
#include <Imagine/Graphics.h>
using namespace Imagine;

class pixel {
    //int x,y;      // position
    Color col;      // Color
    double c,d;     // Confidence and Data term
    bool v;         // 0 if not visited yet, 1 else

public:
    //int getX();
    //int getY();
    Color getColor();
    double getConfidence();
    double getData();
    double getPriority();
    bool getV();

    void setV(int v1);
    void initPixel(Color col1, double c1, double d1, bool v1);
    void setBlanck();    // To initialize the pixels in the target zone

    bool operator==(pixel p);
};


