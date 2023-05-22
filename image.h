#pragma once
#include <Imagine/Graphics.h>
#include "pixel.h"
#include <Imagine/Images.h>
using namespace Imagine;

// On utilise le type Imagine::Image<AlphaColor>
/* Methode de la classe
 * I.weight()
 * I.height()
 * Pour accéder à un pixel : I(x,y)
 * Pour modifier un pixel : I(x,y)=p;
 * Faire une copie : I.copy();
*/

void getFilledMap(Imagine::Image<pixel> I, Imagine::Image<bool> B);
Window affiche(Imagine::Image<pixel> I, int coeff);
bool getImage(Imagine::Image<pixel> &I, std::string imageLink, int argc, char* argv[]);
void compute_and_changeConfidence(Imagine::Image<pixel> I, pixel p, int n);
// A CODER
int translatation(int x, int y, int xd, int yd, int xa, int ya);
void toImageByte(Imagine::Image<pixel> I, Imagine::Image<byte> Ib);
