// Imagine++ project
// Project:  Projet S2
// Student(s): Philomène Boisnard, Erwann Estève, Wandrille Flamant, Sixtine Nodet

#include "image.h"
#include <iostream>
#include "matching.h"

const int width = 512, height = 512;

/*
int testPhilo(){
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
    endGraphics();
    return 0 ;
}
*/

void testMatching1(int argc, char* argv[]){
    initRandom();
    Imagine::Image<pixel> I1(100,200);  //Image I1
    getImage(I1,srcPath("ImageSimple.png"),argc,argv);
    affiche(I1,1);
    click();
    pixel testpixel(rand()%(I1.width()-40)+20,I1.height()/2);
    fillCircle(testpixel.getX(),testpixel.getY(),3,RED);
    int sizeTamp=20;
    drawRect(testpixel.getX()-sizeTamp,testpixel.getY()-sizeTamp,2*sizeTamp+1,2*sizeTamp+1,RED);
    click();
    Imagine::FVector<int,2> goodMatch(0,0);
    matching1(goodMatch.x(),goodMatch.y(),I1,testpixel.getX(),testpixel.getY(),sizeTamp);
    std::cout<<"x="<<goodMatch.x()<<", y="<<goodMatch.y()<<std::endl;
    fillCircle(goodMatch.x(),goodMatch.y(),3,BLUE);
    drawRect(goodMatch.x()-sizeTamp,goodMatch.y()-sizeTamp,2*sizeTamp+1,2*sizeTamp+1,BLUE);
    endGraphics();
}

void testMatching2(int argc, char* argv[]){
    initRandom();
    Imagine::Image<pixel> I1(100,200);  //Image I1
    getImage(I1,srcPath("landscape.png"),argc,argv);
    affiche(I1,1);
    click();
    pixel testpixel(rand()%(I1.width()-40)+20,rand()%(I1.height()-40)+20);
    drawPoint(testpixel.getX(),testpixel.getY(),RED);
    int sizeTamp=1;
    drawRect(testpixel.getX()-sizeTamp,testpixel.getY()-sizeTamp,2*sizeTamp,2*sizeTamp,RED);
    click();
    Imagine::FVector<int,2> goodMatch(0,0);
    matching1(goodMatch.x(),goodMatch.y(),I1,testpixel.getX(),testpixel.getY(),sizeTamp);
    std::cout<<"x="<<goodMatch.x()<<", y="<<goodMatch.y()<<std::endl;
    drawPoint(goodMatch.x(),goodMatch.y(),BLUE);
    drawRect(goodMatch.x()-sizeTamp,goodMatch.y()-sizeTamp,2*sizeTamp,2*sizeTamp,BLUE);
    endGraphics();
}

int main(int argc, char* argv[]) {
    testMatching1(argc,argv);
	return 0;
}
