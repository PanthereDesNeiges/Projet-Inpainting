#pragma once
#include "image.h"

void matching1(int& Qx, int& Qy, Imagine::Image<pixel> I, int Px, int Py, int n); //Cherche un matching parfait du tampon en (Px,Py)
int dist1tampon(int x, int y, int xc, int yc, int n, Imagine::Image<pixel> I, Imagine::Image<bool> filled);
int matching2(int& Qx, int& Qy, Imagine::Image<pixel> I, int Px, int Py, int n); //Cherche le meilleur matching du tampon en (Px,Py)
