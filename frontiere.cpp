#include "frontiere.h"
#include <cmath>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;

void frontiere::add_frontiere(std::vector<pixel> v){
    std::list<pixel>::iterator it;
    int n=v.size();
    int k=0;
    for (it=f.begin();it!=f.end();++it){
        if (it==f.begin()){
        }
        else {
            for (int i=0;i<n;i++){
                if ((*it)==v[i]){
                    if (v[i+1].getV()==0){
                        for(int j=1;j<n;j++){
                            k=(i+j)%n;
                            if (v[k].getV()==0){
                                it=f.insert(it,v[k]);
                            }
                        }
                    }
                    else {
                        for(int j=1;j<n;j++){
                            k=(i-j)%n;
                            if (v[k].getV()==0){
                                it=f.insert(it,v[k]);
                            }
                        }
                    }
                }
            }
        }
    }
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
/*  CHANGER LE image EN Imagine::Image<pixel>
void frontiere::changeData(image I){
    std::list<pixel>::iterator it;
    int x;
    int y;
    double d;
    for (it=f.begin();it!=f.end();++it){
        x=(*it).getX();
        y=(*it).getY();
        d=I.getPixel(x,y).getData();
        (*it).setData(d);
    }
}

double compute_confidence(image I, int n, int x, int y){
    double S=0;
    for (int i=0;i<2*n+1;i++){
        for (int j=0;j<2*n+1;j++){
            if (I.getPixel(x-n+i,y-n+j).getV()){
                S+=I.getPixel(x-n+i,y-n+j).getConfidence();
            }
        }
    }
    S=double(S/((2*n+1)*(2*n+1)));
    return (S);
}

void frontiere::compute_and_change_confidence(image I,int n){
    std::list<pixel>::iterator it;
    int x;
    int y;
    double c;
    for (it=f.begin();it!=f.end();++it){
        x=(*it).getX();
        y=(*it).getY();
        c=compute_confidence(I,n,x,y);
        (*it).setConfidence(c);
    }
}
*/
