// Imagine++ project
// Project:  Projet S2
// Student(s): Philomène Boisnard, Erwann Estève, Wandrille Flamant, Sixtine  Nodet

#include <Imagine/Graphics.h>
using namespace Imagine;
#include "pixel.h"


const int width = 512, height = 512;

void f(){
    openWindow(width,height);

    std::cout<<"Cliquez pour sélectionner les points de la frontière, clic droit pour finir";
    std::vector<pixel> v;
    int x,y,m=0;
    getMouse(x,y);
    while (m==1) {
        v.push_back(pixel(x,y));
        m=getMouse(x, y);
        if(m==1)
            drawLine(x,y,v.back().getX(),v.back().getY(),RED);
    }
    drawLine(v.front().getX(),v.front().getY(),v.back().getX(),v.back().getY(),RED);
    endGraphics();

}
int main() {
	return 0;
}
