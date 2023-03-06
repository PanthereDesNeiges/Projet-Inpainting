#include "frontiere.h"
#include <cmath>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;

void frontiere::add_frontiere(vector<){

}

void frontiere::initialize_frontiere(){

}

void frontiere::pop_frontiere(){

}

pixel frontiere::max_priority(){
    std::list<pixel>::iterator it;
    pixel max;
    for (it=f.begin();it!=f.end();++it){
        if ((*it).getPriority()>max.getPriority()){
            max=*it;
        }
    }
    return (max);
}
