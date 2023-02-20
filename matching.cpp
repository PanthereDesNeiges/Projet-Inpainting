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

pixel image::getData(int x, int y) {
    return data[y*w + x];
}

void image::setPixel(int x, int y, pixel p) {
    data[y*w + x] = p;
}
