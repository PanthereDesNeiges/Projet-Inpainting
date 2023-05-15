// Imagine++ project
// Project:  Projet S2
// Student(s): Philomène Boisnard, Erwann Estève, Wandrille Flamant, Sixtine Nodet

#include "image.h"
#include <iostream>
#include "matching.h"
#include "frontiere.h"

const int width = 512, height = 512;


int f(int x, int y, pixel X1, pixel X2){
    return (x-X1.getX())*(X2.getY()-X1.getY())
            - (y-X1.getY())*(X2.getX()-X1.getX());
}

std::vector<pixel> expand(std::vector<pixel> v){
    std::vector<pixel> v1;
    pixel X1, X2;
    X2=v.data()[v.size()-1];
    int x=X2.getX();
    int y=X2.getY();
    for(int i=0;i<(int)v.size();i++){
        X1=X2;
        X2=v.data()[i];
        while(x!=X2.getX()&&y!=X2.getY()){
            v1.push_back(pixel(x,y));
            if (f(x,y+1,X1,X2)>0&&f(x,y,X1,X2)>=0)
                    y-=1;
            else if (f(x,y+1,X1,X2)<0&&f(x,y,X1,X2)<=0)
                    y+=1;
            else if (f(x+1,y,X1, X2)>0&&f(x,y,X1,X2)>=0)
                    x-=1;
            else if (f(x+1,y,X1, X2)<0&&f(x,y,X1,X2)<=0)
                    x+=1;
        }
    }
    return v1;
}

int testPhilo(int argc, char* argv[]){
    /*
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

    // RELIER LES POINTS
    std::vector<pixel> v1 = expand(v);

*/
    Imagine::Image<pixel>I;
    getImage(I,srcPath("apple.png"), argc, argv);
    std::vector<pixel> v;
    affiche(I,1);
    initialize_frontiere(I,v);

    endGraphics();
    return 0 ;
}


void testMatching1(int argc, char* argv[]){
    initRandom();
    Imagine::Image<pixel> I1(100,200);  //Image I1
    getImage(I1,srcPath("apple.png"),argc,argv);
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

int main(int argc, char* argv[]) {
    testPhilo(argc,argv);
	return 0;
}
