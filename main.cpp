// Imagine++ project
// Project:  Projet S2
// Student(s): Philomène Boisnard, Erwann Estève, Wandrille Flamant, Sixtine  Nodet

#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
using namespace Imagine;
#include "pixel.h"


const int width = 512, height = 512;

int f(){

    // CHARGER ET AFFICHER L'IMAGE

    Image<byte> I;
    const char* fic1 = srcPath("zebra.png");
    if(! load(I, fic1)) {
        std::cout << "Probleme dans le chargement d'images" << std::endl;
        return 1;
    }
    openWindow(I.width(),I.height());
    display(I);

    // SELECTIONNER LES POINTS DU CONTOUR DANS UN VECTEUR

    std::cout<<"Cliquez pour selectionner les points de la frontiere, clic droit pour finir (3 points au moins)\n";
    std::vector<pixel> v;
    int x,y,m;
    getMouse(x,y);
    for (int i=0; i<2;i++){
        v.push_back(pixel(x,y));
        m=getMouse(x, y);
        drawLine(x,y,v.back().getX(),v.back().getY(),RED);
    }
    while (m==1) {
        v.push_back(pixel(x,y));
        m=getMouse(x, y);
        if(m==1)
            drawLine(x,y,v.back().getX(),v.back().getY(),RED);
    }
    drawLine(v.front().getX(),v.front().getY(),v.back().getX(),v.back().getY(),RED);

    //








    endGraphics();
    return 0 ;
}
int main() {
    f();    //test (a supprimer à votre convenance)
	return 0;
}
