#include "frontiere.h"
#include <cmath>
using namespace std;

bool visited_voisins(pixel p,Imagine::Image<pixel> I){
    //retourne true si un des voisins de p est rempli, false sinon
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

/*
void frontiere::add_frontiere(std::vector<pixel> v,Imagine::Image<pixel> I){
//v contient les elements de la frontiere du tampon
// ajoute les elements de la frontiere du tampon qui définissent la nouvelle zone target dans la frontiere
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
*/
void frontiere::add_frontiere(std::vector<pixel> v, Imagine::Image<pixel> I){
    std::list<pixel>::iterator it=f.end();
    for(int i=0; i<v.size(); i++){
        if (!I(v[i].getX(),v[i].getY()).getV()){
            it=f.insert(it,v[i]);
        }
    }
}

void frontiere::add_frontiere_initialise(std::vector<pixel> v,Imagine::Image<pixel> I){
// v contient les elements de la frontiere du carré dessiné par l'utilisateur
// ajoute lors de l'initialisation les elements de cette frontiere qui définissent la nouvelle zone target
    std::list<pixel>::iterator it=f.end();
    for(int i=0; i<v.size(); i++){
        it=f.insert(it,v[i]);
    }
}

void frontiere::initialize_frontiere(std::vector<pixel> v){
// v contient les elements de la frontiere du premier carre detoure par l'utilisateur
// cette fonction ajoute tous les elements de v a la frontiere
    int s=v.size();
    std::list<pixel>::iterator it;
    it=f.begin();
    for (int i=0;i<s;i++){
        it=f.insert(it,v[i]);
    }
}


void frontiere::pop_frontiere(std::vector<pixel> v){
// cette fonction retire de la frontiere tous les elements contenus dans le vecteur v
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
/*
void frontiere::pop_frontiere(std::vector<pixel> v){
    // cette fonction retire de la frontiere tous les elements contenus dans le vecteur v
    for (int i=0; i<(int)v.size(); i++){
        for (std::list<pixel>::iterator it=f.begin();it!=f.end();){
            if((*it).getX()==v[i].getX()&&(*it).getY()==v[i].getY()){
                it=f.erase(it);
            }
            else{
                it++;
            }
        }
    }
}
*/
pixel frontiere::max_priority(){
// cette fonction parcourt la frontiere et retourne le pixel qui a la priorite maximale
    std::list<pixel>::iterator it;
    pixel max=*f.begin();
    for (it=f.begin();it!=f.end();++it){
        if ((*it).getPriority()>max.getPriority()){
            max=*it;
        }
    }
    return (max);
}

void gradient_and_normal_frontiere(double gradient[2],double normal[2],Imagine::Image<pixel> I1, pixel a, Imagine::Image<byte> I2){
// cette fonction calcule le gradients et le vecteur normal unitaire au pixel p (appartenant a la frontiere)
// on fixe le gradient et le vecteur normal unitaire a zero pour les pixels trop proche des bords de l'image et pour les pixels situes aux angles droits de la frontiere
    int w = I1.width();
    int h = I1.height();
    int x = a.getX();
    int y = a.getY();
    normal[0]=0;
    normal[1]=0;
    gradient[0]=0;
    gradient[1]=0;
    if (x==0 || x==w-1){
    }

    else if (I1(x+1,y).getV()){
        if (I1(x-1,y).getV()){
            gradient[0]=double(I2(x+1,y)-I2(x-1,y))/2;
            if (I1(x,y+1).getV()){
                normal[0]=0;
                normal[1]=1;
            }
            else {
                normal[0]=0;
                normal[1]=-1;
            }
        }
        else {
            gradient[0]=double(I2(x+1,y)-I2(x,y))/2;
        }
    }

    else if (I1(x-1,y).getV()){
        gradient[0]=double(I2(x,y)-I2(x-1,y))/2;
    }

    if ( y==0 || y==h-1){
    }

    else if (I1(x,y+1).getV()){
        if (I1(x,y-1).getV()){
            gradient[0]=double(I2(x,y+1)-I2(x,y-1))/2;
            if (I1(x+1,y).getV()){
                normal[0]=1;
                normal[1]=0;
            }
            else {
                normal[0]=0;
                normal[1]=-1;
            }
        }
        else {
            gradient[0]=double(I2(x,y+1)-I2(x,y))/2;
        }
    }

    else if (I1(x,y-1).getV()){
        gradient[0]=double(I2(x,y-1)-I2(x,y))/2;
    }
}

double Data(double gradient[2],double normal[2]){
// calcule le terme data a partir d'un gradient et d'un vecteur normal unitaire
    double D=0;
    D+=gradient[0]*normal[0];
    D+=gradient[1]*normal[1];
    if (D<0){
        D=-D;
    }
    D=double(D/alpha);
    return (D);
}

void frontiere::changeData(Imagine::Image<pixel> I){
// parcourt tous les elements de la frontiere, calcule et change le terme data de ceux-ci
    int w=I.width();
    int h=I.height();
    Imagine::Image<byte> I2(w,h);
    toImageByte(I,I2);
    std::list<pixel>::iterator it;
    double gradient[2];
    double normal[2];
    double G;
    for (it=f.begin();it!=f.end();++it){
        gradient_and_normal_frontiere(gradient,normal,I,(*it),I2);
        G=Data(gradient,normal);
        (*it).setData(G);
    }
}

std::vector<pixel> frontiere_tampon(Imagine::Image<pixel> I1,int x, int y, int n){
// retourne un vecteur dans lequel est contenu tous les elements de la frontiere d'un tampon
    std::vector<pixel> v;
    v.clear();
    for (int i=-n;i<=n;i++){
        v.push_back(I1(x-n,y+i));
    }
    for (int i=-n;i<=n;i++){
        v.push_back(I1(x+n,y+i));
    }
    for (int i=-n+1;i<=n-1;i++){
        v.push_back(I1(x+i,y-n));
    }
    for (int i=-n+1;i<=n-1;i++){
        v.push_back(I1(x+i,y+n));
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

void frontiere::affiche(){
    for(std::list<pixel>::iterator it=f.begin(); it!=f.end(); it++){
        drawPoint((*it).getX(),(*it).getY(),BLACK);
    }
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


void add_frontiere(Imagine::Image<pixel> I1,std::vector<pixel> &v, int x1, int y1, int x2, int y2){
    for (int i=0;i<=abs(x1-x2);i++){
        v.push_back(I1(min(x1,x2)+i,y1));
    }
    for (int i=0;i<=abs(x1-x2);i++){
        v.push_back(I1(min(x1,x2)+i,y2));
    }
    for (int i=1;i<abs(y1-y2);i++){
        v.push_back(I1(x1,min(y1,y2)+i));
    }
    for (int i=1;i<abs(y1-y2);i++){
        v.push_back(I1(x2,min(y1,y2)+i));
    }
}

void frontiere::clear_frontiere_not_vis(Imagine::Image<pixel> I1){
    for(std::list<pixel>::iterator it=f.begin();it!=f.end();){
        if(!I1((*it).getX(),(*it).getY()).getV()){
            it=f.erase(it);
        }
        else{
            ++it;
        }
    }
}

void frontiere::clear_frontiere_between(int Px, int Py, int tailleTampon){
    for(std::list<pixel>::iterator it=f.begin();it!=f.end();){
        if((*it).getX()>Px-tailleTampon&&(*it).getX()<Px+tailleTampon&&(*it).getY()>Py-tailleTampon&&(*it).getY()<Py+tailleTampon){
            it=f.erase(it);
        }
        else{
            ++it;
        }
    }
}
