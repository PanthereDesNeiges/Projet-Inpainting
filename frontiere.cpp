#include "frontiere.h"
#include <cmath>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;

void frontiere::add_frontiere(int x1, int y1, int x2, int y2){

}

void frontiere::initialize_frontiere(std::vector<pixel> v){

}

void frontiere::pop_frontiere(std::vector<pixel> v){
    std::list<pixel>::iterator it;
    int x1 = v[0].getX();
    int y1 = v[0].getY();
    int x2 = v[-1].getX();
    int y2 = v[-1].getY();
    for (it=f.begin();it!=f.end();++it){
        if ((*it).getX()<x2 && (*it).getX()>x1 && (*it).getY()>y1 && (*it).getY()<y2){
            it=f.erase(it);
        }
    }
}

pixel frontiere::max_priority(){
    std::list<pixel>::iterator it;
    pixel max=*f.begin();
    for (it=f.begin();it!=f.end();++it){
        if ((*it).getPriority()>max.getPriority()){
            max=*it;
        }
    }
    return (max);
}

void frontiere::change_confidence_and_data(image I){
    std::list<pixel>::iterator it;
    int x;
    int y;
    for (it=f.begin();it!=f.end();++it){
        x=(*it).getX();
        y=(*it).getY();
        double c=I.getPixel(x,y).getConfidence();
        double d=I.getPixel(x,y).getData();
        (*it).setConfidence(c);
        (*it).setData(d);
    }
}
