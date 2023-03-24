#pragma once
#include <Imagine/Graphics.h>
using namespace Imagine;
#include <Imagine/Images.h>
using namespace Imagine;
#include "pixel.h"

// On utilise le type Imagine::Image<AlphaColor>
/* Methode de la classe
 * I.weight()
 * I.height()
 * Pour accéder à un pixel : I(x,y)
 * Pour modifier un pixel : I(x,y)=p;
 * Faire une copie : I.copy();
*/

void getFilledMap(Imagine::Image<pixel> I, bool B[],int wb,int hb);
void affiche(Imagine::Image<pixel> I, int coeff);
bool getImage(Imagine::Image<pixel> &I, std::string imageLink, int argc, char* argv[]);
void changeConfidence(Imagine::Image<pixel> I, pixel p, int n);
// A CODER
int translatation(int x, int y, int xd, int yd, int xa, int ya);
