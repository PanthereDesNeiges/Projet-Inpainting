#pragma once
#include "image.h"

class frontiere {
    std::list<pixel> f;
public:
    void add_frontiere(std::vector<pixel> v,Imagine::Image<pixel> I); // ajoute les elements de v, v etant la fontiere du tampon, dans la frontiere
    void initialize_frontiere(std::vector<pixel> v);   // prend en argument la liste de points à partir de laquelle on fait la frontière
    void pop_frontiere();
    void pop_frontiere(std::vector<pixel> v);   //prend en argument le tampon
    pixel max_priority();
    void changeData(Imagine::Image<pixel> I);   //prend en argument l'image
    void compute_and_change_confidence(Imagine::Image<pixel> I,int n);
};

//double compute_confidence(image I, int n, int x, int y)
