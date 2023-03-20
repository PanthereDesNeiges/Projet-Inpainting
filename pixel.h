#pragma once
#include <Imagine/Graphics.h>
using namespace Imagine;
AlphaColor col;
class pixel {
    int x,y;        // position
    Color col;      // Color
    double c,d;     // Confidence and Data term
    bool v;         // 0 if not filled yet, 1 else

public:
    pixel();
    pixel(int X,int Y);
    int getX();
    int getY();
    Color getColor();
    double getConfidence();
    double getData();
    double getPriority();
    bool getV();
    void setConfidence(double conf);
    void setData(double data);
    void setColor(AlphaColor color);
    void setX(int val);
    void setY(int val);
    void setV(int v1);
    void initPixel(Color col1, double c1, double d1, bool v1);
    void setBlanck();    // To initialize the pixels in the target zone

    bool operator==(pixel p);
    const pixel& operator=(const pixel& p);
};


