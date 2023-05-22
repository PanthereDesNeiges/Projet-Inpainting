#include "image.h"
#include <cmath>
using namespace std;

void getFilledMap(Imagine::Image<pixel> I, Imagine::Image<bool> B){ // Prends une image I et modifie l'image de bool B de façon à en faire la "carte
    int h=I.height(), w=I.width();                                  //  des pixel rempli" (qui sera plus facile à manier
    assert(h==B.height() and w==B.width()); // Erreur si l'image B est de mauvaise taille
    for(int i=0; i<w; i++){
        for(int j=0; j<h; j++){
            B(i,j)=I(i,j).getV();           //getV = 1 si le pixel est rempli, 0 si il est vide
        }
    }
}

Window affiche(Imagine::Image<pixel> I, int coeff){
    int w=I.width(), h=I.height();
    Imagine::Image<Color> I0(w,h);
    for (int i=0;i<w;i++){
        for(int j=0; j<h; j++){
            I0(i,j)=I(i,j).getColor();
        }
    }

    Imagine::display(I0,0,0,false,coeff);
}

bool getImage(Imagine::Image<pixel> &I,std::string imageLink, int argc, char* argv[]){    // Transverse l'image de lien imageLink (.png) dans l'image I
    Imagine::Image<AlphaColor> I0;  // Image tampon pour récupérer le PNG
    if(! load(I0, argc>1? argv[1]: imageLink)) {
        std::cout << "Echec de lecture d'image" << std::endl;
        return 0;
    }
    int w=I0.width(), h=I0.height();
    I.setSize(w,h);                 // On modifie la taille de I de façon à coller à l'image chargée
    for (int i=0;i<w;i++){
        for (int j=0;j<h;j++){      // Mise en place des paramètres de chaque pixel
            I(i,j).setX(i);
            I(i,j).setY(j);
            I(i,j).setConfidence(1);
            I(i,j).setData(0);
            I(i,j).setColor(I0(i,j));
            I(i,j).setV(true);
        }
    }
    return true;
}

void compute_and_changeConfidence(Imagine::Image<pixel> I, pixel p, int n){     //Applique la confiance du pixel p aux pixels alentour
    int x=p.getX();
    int y=p.getY(); // coordonnées du pixel de la frontière autour duquel on applique le tampon
    double c=0;
    for (int i=0;i<2*n+1;i++){
        for (int j=0;j<2*n+1;j++){
            if (I(x-n+i,y-n+j).getV()){
                c+=I(x-n+i,y-n+j).getConfidence();
            }
        }
    }
// somme des confiances des pixels déjà rempli du tampon

    c=double(c/((2*n+1)*(2*n+1))); // normalisation du terme de confiance par l'aire du tampon

    for (int i=0;i<2*n+1;i++){
        for (int j=0;j<2*n+1;j++){
            if (!I(x-n+i,y-n+j).getV()){
                I(x-n+i,y-n+j).setConfidence(c);
            }
        }
    }
// met à jour la confiance des termes nouvellement empli du tampon
}

void toImageByte(Imagine::Image<pixel> I, Imagine::Image<byte> Ib){ // Modifie Ib de façon à en faire l'image des intensités lumineuses (en noir et blanc)
    int w=I.width(), h=I.height();
    assert(w==Ib.width() && h==Ib.height());                        //Erreur si les tailles des tableaux ne correspondent pas
    for(int i=0; i<w; i++){
        for(int j=0; j<h; j++){
            Ib(i,j)=byte((int(I(i,j).getColor().r()) + int(I(i,j).getColor().g()) + int(I(i,j).getColor().b()))/3);
        }
    }
}
