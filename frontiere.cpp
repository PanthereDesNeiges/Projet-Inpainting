#include "frontiere.h"
#include <cmath>
using namespace std;

bool visited_voisins(pixel p,Imagine::Image<pixel> I){
    //retourne true si un des voisins est rempli, false sinon
    int w=I.width();
    int h=I.height();
    int x=p.getX();
    int y=p.getY();
    if (x!=0 && y!=0 && y!=h-1){
        if (!I(x+1,y).getV()){
            return (false);
        }
        else if (!I(x+1,y+1).getV()){
            return (false);
        }
        else if (!I(x+1,y-1).getV()){
            return (false);
        }
        else if (!I(x,y+1).getV()){
            return (false);
        }
        else if (!I(x,y-1).getV()){
            return (false);
        }
    }
    else if (x!=w-1 && y!=0 && y!=h-1){
        if (!I(x-1,y+1).getV()){
            return (false);
        }
        else if (!I(x-1,y).getV()){
            return (false);
        }
        else if (!I(x-1,y-1).getV()){
            return (false);
        }
    }
    else if (y==0){
        if (!I(x,y+1).getV()){
            return (false);
        }
        if (x!=0){
            if (!I(x-1,y+1).getV()){
                return (false);
            }
            else if (!I(x-1,y).getV()){
                return (false);
            }
        }
        if (x!=h-1){
            if (!I(x+1,y+1).getV()){
                return (false);
            }
            else if (!I(x+1,y).getV()){
                return (false);
            }
        }
    }
    else if (y==h-1){
        if (!I(x,y-1).getV()){
            return (false);
        }
        if (x!=0){
            if (!I(x-1,y-1).getV()){
                return (false);
            }
            else if (!I(x-1,y).getV()){
                return (false);
            }
        }
        if (x!=h-1){
            if (!I(x+1,y-1).getV()){
                return (false);
            }
            else if (!I(x+1,y).getV()){
                return (false);
            }
        }
    }
    return (true);
}

void frontiere::add_frontiere(std::vector<pixel> v,Imagine::Image<pixel> I){
    std::list<pixel>::iterator it;
    int n=v.size();
    int k=0;
    int c=0;
    // on parcourt l'ensemble des elements de la frontiere
    for (it=f.begin();it!=f.end();++it){
        if (it==f.begin()){
        }
        // on passe le premier element
        else {
            for (int i=0;i<n;i++){
                // on parcourt la liste v qu'on veut ajouter
                if ((*it)==v[i] && c==0){
                    c=1;
                    //lorsque l'on trouve le point commun entre la frontiere et la frontiere du tampon, on ajoute à cet endroit tous les elements de v
                    if (!visited_voisins(v[(i+1)%n],I)){
                        for(int j=1;j<n;j++){
                            k=(i+j)%n;
                            if (!visited_voisins(v[k],I)){
                                it=f.insert(it,v[k]);
                            }
                        }
                    }
                    else {
                        for(int j=1;j<n;j++){
                            k=int(i-j) % n;
                            if (k<0){
                                k=n+k;
                            }
                            if (!visited_voisins(v[k],I)){
                                it=f.insert(it,v[k]);
                            }
                        }
                    }
                }
            }
        }
    }
}

void frontiere::add_frontiere_initialise(std::vector<pixel> v,Imagine::Image<pixel> I){
    std::list<pixel>::iterator it;
    int n=v.size();
    int k=0;
    int c=0;
    // on parcourt l'ensemble des elements de la frontiere
    for (it=f.begin();it!=f.end();++it){
        if (it==f.begin()){
        }
        // on passe le premier element
        else {
            for (int i=0;i<n;i++){
                // on parcourt la liste v qu'on veut ajouter
                if ((*it)==v[i] && c==0){
                    c=1;
                    //lorsque l'on trouve le point commun entre la frontiere et la frontiere du tampon, on ajoute à cet endroit tous les elements de v
                    if (visited_voisins(v[(i+1)%n],I)){
                        for(int j=1;j<n;j++){
                            k=(i+j)%n;
                            if (visited_voisins(v[k],I)){
                                it=f.insert(it,v[k]);
                            }
                        }
                    }
                    else {
                        for(int j=1;j<n;j++){
                            k=int(i-j) % n;
                            if (k<0){
                                k=n+k;
                            }
                            if (visited_voisins(v[k],I)){
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
    int s=v.size();
    std::list<pixel>::iterator it;
    it=f.begin();
    for (int i=0;i<s;i++){
        it=f.insert(it,v[i]);
    }
}

void frontiere::pop_frontiere(std::vector<pixel> v){
    std::list<pixel>::iterator it;
    int s=v.size()-1;
    int x1 = v[0].getX();
    int y1 = v[0].getY();
    int x2 = v[s].getX();
    int y2 = v[s].getY();
    for (it=f.begin();it!=f.end();){
        if ((*it).getX()<x2 && (*it).getX()>x1 && (*it).getY()>y1 && (*it).getY()<y2){
            it=f.erase(it);
        }
        else {
            ++it;
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

std::vector<pixel> frontiere_tampon(Imagine::Image<pixel> I1,int x, int y, int n){
    std::vector<pixel> v;
    v.clear();
    for (int i=0;i<2*n+1;i++){
        v.push_back(I1(x-n,y-n+i));
    }
    for (int i=1;i<2*n+1;i++){
        v.push_back(I1(x+n,y+n-i));
    }
    for (int i=1;i<2*n;i++){
        v.push_back(I1(x+n-i,y-n));
    }
    for (int i=1;i<2*n+1;i++){
        v.push_back(I1(x-n+i,y+n));
    }
    return (v);
}

std::list<pixel>::iterator frontiere::begin(){
    return (f.begin());
}

std::list<pixel>::iterator frontiere::end(){
    return (f.end());
}
bool frontiere::isVoid(){
    return f.size()==0;
}


void initialize_frontiere(Imagine::Image<pixel> I1,std::vector<pixel>& v){
    int x1;
    int y1;
    int x2;
    int y2;
    getMouse(x1,y1);
    fillRect(x1,y1,1,1,BLACK);
    getMouse(x2,y2);
    fillRect(x2,y2,1,1,BLACK);

    for (int i=0;i<abs(x1-x2)+1;i++){
        v.push_back(I1(min(x1,x2)+i,min(y1,y2)));
    }
    for (int i=1;i<abs(y1-y2)+1;i++){
        v.push_back(I1(max(x1,x2),min(y1,y2)+i));
    }
    for (int i=1;i<abs(x1-x2)+1;i++){
        v.push_back(I1(max(x1,x2)-i,max(y1,y2)));
    }
    for (int i=1;i<abs(y1-y2);i++){
        v.push_back(I1(min(x1,x2),max(y1,y2)-i));
    }

    for (int i=x1+1;i<x2;i++){
        for (int j=y1+1;j<y2;j++){
            I1(i,j).setV(0);
        }
    }
}
void initialize_frontiere(Imagine::Image<pixel> I1,std::vector<pixel> &v, int x1, int y1, int x2, int y2){
    for (int i=0;i<abs(x1-x2)+1;i++){
        v.push_back(I1(min(x1,x2)+i,min(y1,y2)));
    }
    for (int i=1;i<abs(y1-y2)+1;i++){
        v.push_back(I1(max(x1,x2),min(y1,y2)+i));
    }
    for (int i=1;i<abs(x1-x2)+1;i++){
        v.push_back(I1(max(x1,x2)-i,max(y1,y2)));
    }
    for (int i=1;i<abs(y1-y2);i++){
        v.push_back(I1(min(x1,x2),max(y1,y2)-i));
    }
}
