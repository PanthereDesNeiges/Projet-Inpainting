#include "pixel.h"
#include "image.h"
#include <cmath>
using namespace std;
#include <Imagine/Graphics.h>
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

int translatation(int x, int y, int xd, int yd, int xa, int ya){
    // renvoie l'indice du sous-pixel de la zone d'arrivée associé à (x,y) dans celle de départ
    return (y*w + x + (ya-yd)*w + (xa-xd));
}

void image::CopyPaste(int xd, int yd, int wd, int hd, int xa, int ya){
    // attention faut que ça reste dans l'image
    // et que le pixel ait pas déjà été colorié
    // prendre en compte que le rectangle est pas trop grand
    int x,y ;
    pixel p;
    for(int i=0; i< wd; i++){
        for(int j=0; j< hd; j++){
            x = xa + i;
            y = ya + i;
            p = getPixel(xd + i, yd + j);
            if(!getPixel(x,y).getV()){
                setPixel(x, y, p);
                // v = 1
                // uptdate confidence et data term
            }
        }
    }
}
