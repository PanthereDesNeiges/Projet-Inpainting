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

void frontiere::compute_and_changeData(image I){
    std::list<pixel>::iterator it;
    pixel p;
    double d;
    int n=f.size();
    int *memoire=new int[2*n];
    int i=0;
    for (it=f.begin();it!=f.end();++it){
        memoire[i]=(*it).getX();
        memoire[i+1]=(*it).getY();
        i+=2;
    }
    i=0;
    for (it=f.begin();it!=f.end();++it){
        p=normal_unitaire(memoire[(i-6)%(2*n)],memoire[(i-5)%(2*n)],memoire[(i+6)%(2*n)],memoire[(i+7)%(2*n)]);
        (*it).setNX(p.getX());
        (*it).setNY(p.getY());
        i+=2;

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


void gradient_frontiere(vector<double> v,Imagine::Image<pixel> I1, pixel a, Imagine::Image<byte> I2){
    int w = I1.width();
    int h = I1.height();

    if (a.getX()==0 || a.getX()==w-1){
        v[0]=0;
        v[1]=0;
    }

    else if (I1(a.getX()+1,a.getY()).getV()){
        if (I1(a.getX()-1,a.getY()).getV()){
            v[0]=double(I2(a.getX()+1,a.getY())-I2(a.getX()-1,a.getY()))/2;
        }
        else {
            v[0]=double(I2(a.getX()+1,a.getY())-I2(a.getX(),a.getY()))/2;
        }
    }

    else if (I1(a.getX()-1,a.getY()).getV()){
        v[0]=double(I2(a.getX(),a.getY())-I2(a.getX()-1,a.getY()))/2;
    }

    if ( a.getY()==0 || a.getY()==h-1){
        v[0]=0;
        v[1]=0;
    }

    else if (I1(a.getX(),a.getY()+1).getV()){
        if (I1(a.getX(),a.getY()-1).getV()){
            v[0]=double(I2(a.getX(),a.getY()+1)-I2(a.getX(),a.getY()-1))/2;
        }
        else {
            v[0]=double(I2(a.getX(),a.getY()+1)-I2(a.getX(),a.getY()))/2;
        }
    }

    else if (I1(a.getX(),a.getY()-1).getV()){
        v[0]=double(I2(a.getX(),a.getY()-1)-I2(a.getX(),a.getY()))/2;
    }
}

double Data(vector<double> gradient,vector<double> normal){
    double D=0;
    D+=gradient[0]*normal[0];
    D+=gradient[1]*normal[1];
    if (D<0){
        D=-D;
    }
    D=double(D/alpha);
    return (D);
}
