#pragma once
#include "image.h"

void matching1(int& Qx, int& Qy, Imagine::Image<pixel> I, int Px, int Py, int n); //Cherche un matching parfait du tampon en (Px,Py)
void matching2(int& Qx, int& Qy, Imagine::Image<pixel> I, int Px, int Py, int n); //Cherche le meilleur matching du tampon en (Px,Py)
