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


void image::CopyPaste(int xd, int yd, int wd, int hd, int xa, int ya){
    /*
        attention :
    faut que ça reste dans l'image (checker coord du pixel d'arrivée)
    et que le pixel ait pas déjà été colorié
    prendre en compte quand le rectangle est trop grand
    update confidence, data term et v du pixel collé à chaque fois

        En argument :
    (xd,yd) et (xa,ya) correspondent aux coordonées du coin haut gauche du rectangle qui va être copié-collé
    la zone de départ est un rectangle de largeur et hauteur wd et hd.
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
