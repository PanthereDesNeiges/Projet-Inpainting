#include "pixel.h"
#include "image.h"
#include <cmath>
using namespace std;
#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
using namespace Imagine;
#include <Imagine/Images.h>
using namespace Imagine;


/* ******************************* */


// Implémentation du constructeur
image::image(int width, int height) : w(width), h(height) {
    // Alloue de la mémoire pour le tableau de pixels
    data = new pixel[w*h];
}

// Implémentation du destructeur
image::~image() {
    // Libère la mémoire allouée pour le tableau de pixels
    delete [] data;
}

// Implémentation des autres méthodes
int image::getW() {
    return w;
}

int image::getH() {
    return h;
}

pixel image::getPixel(int x, int y) {
    return data[y*w + x];
}

void image::setPixel(int x, int y, pixel p) {
    data[y*w + x] = p;
}


void image::CopyPaste(int xd, int yd, int wd, int hd, int xa, int ya){
    /*
    *    attention :
    *faut que ça reste dans l'image (checker coord du pixel d'arrivée)
    *et que le pixel ait pas déjà été colorié
    *prendre en compte quand le rectangle est trop grand
    *update confidence, data term et v du pixel collé à chaque fois
    *
    *    En argument :
    *(xd,yd) et (xa,ya) correspondent aux coordonées du coin haut gauche du rectangle qui va être copié-collé
    *la zone de départ est un rectangle de largeur et hauteur wd et hd.
    */

    int x,y ;
    pixel p;
    for(int i=0; i< wd; i++){
        for(int j=0; j< hd; j++){
            x = xa + i;
            y = ya + i;
            p = getPixel(xd + i, yd + j);
            if(!getPixel(x,y).getV()){
                setPixel(x, y, p);
                // uptdate param
            }
        }
    }
}

void image::getFilledMap(bool B[],int wb,int hb){ // Prends une image et modifie B de façon à en faire la "carte des pixel rempli" (w et h sont les tailles de b)
    assert(h==hb and w==wb); // Tableau B de mauvaise taille
    for(int i=0; i<w; i++){
        for(int j=0; j<h; j++){
            B[i+w*j]=data[i+w*j].getV();
        }
    }
}

Imagine::Image< AlphaColor, 2 > image::getImagineImage(){
    Imagine::Image< AlphaColor, 2 > I(getW(),getH());
    for(int i=0; i< getW(); i++){
        for(int j=0; j<getH(); j++){
            I[i][j] = getPixel(i,j).getColor();
        }
    }
    return I;
}

void image::display(int coeff){
    // normalement ça devrait afficher l'image multiplié par le coeff
    Imagine::Image< AlphaColor, 2 > I =getImagineImage();
    openWindow(getW()*coeff, getH()*coeff);
    Imagine::display(I,0,0,false,coeff);
}


bool image::getImage(std::string imageLink, int argc, char* argv[]){    // Transverse l'image de lien imageLink (.png) dans l'image I
    Imagine::Image<AlphaColor> I;
    if(! load(I, argc>1? argv[1]: imageLink)) {
        std::cout << "Echec de lecture d'image" << std::endl;
        return 0;
    }
    w=I.width();
    h=I.height();
    delete [] data;
    data = new pixel[w*h];
    for (int k=0;k<w*h;k++){
        data[k].setX(k%w);
        data[k].setY(k/w);
        data[k].setConfidence(0);
        data[k].setData(0);
        data[k].setColor(I(data[k].getX(),data[k].getY()));
        data[k].setV(false);
    }
    return true;
}

