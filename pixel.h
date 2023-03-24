#pragma once
#include <Imagine/Graphics.h>
using namespace Imagine;

const int alpha=255;

class pixel {
    int x,y;        // position
    Color col;      // Color
    double c,d;     // Confidence and Data term
    bool v;         // 0 if not visited yet, 1 else
    int nx,ny;      // vecteur normal unitaire (quand dans la frontiere)

public:
    pixel();
    pixel(int X,int Y);
    int getX();
    int getY();
    int getNX();
    int getNY();
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
    void setNX(int val);
    void setNY(int val);
    void setV(int v1);
    void initPixel(Color col1, double c1, double d1, bool v1);
    void setBlanck();    // To initialize the pixels in the target zone

    bool operator==(pixel p);
    const pixel& operator=(const pixel& p);
};

double norme(pixel p);
pixel normal_unitaire(int x1,int y1, int x2, int y2);
