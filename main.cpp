// Imagine++ project
// Project:  Projet S2
// Student(s): Philomène Boisnard, Erwann Estève, Wandrille Flamant, Sixtine  Nodet

#include <Imagine/Graphics.h>
using namespace Imagine;
#include "pixel.h"
#include "image.h"


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
void testErwann(int argc, char* argv[]){
    image I1(100,200);  //Image I1
    I1.getImage(srcPath("japanese.png"),argc,argv);
    Window W1=openWindow(I1.getW(),I1.getH());
    click();
    endGraphics();
}
int main(int argc, char* argv[]) {
    testErwann(argc,argv);
	return 0;
}
