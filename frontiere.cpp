#include "frontiere.h"
#include <cmath>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;

void frontiere::add_frontiere(pixel p){

}

void frontiere::initialize_frontiere(std::vector<pixel> v){

}

void frontiere::pop_frontiere(std::vector<pixel> v){
    std::list<pixel>::iterator it;
    for (it=f.begin();it!=f.end();++it){
        for (int i=0;i<v.size();i++){
            if ((*it).getX()==v[i].getX() && (*it).getY()==v[i].getY()){
                it=f.erase(it);
            }
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
