// Imagine++ project
// Project:  Projet S2
// Student(s): Philomène Boisnard, Erwann Estève, Wandrille Flamant, Sixtine Nodet

#include "frontiere.h"
#include <iostream>
#include "matching.h"
#include "frontiere.h"

const int width = 512, height = 512;


int f(int x, int y, pixel X1, pixel X2){
    return (x-X1.getX())*(X2.getY()-X1.getY())
            - (y-X1.getY())*(X2.getX()-X1.getX());
}

std::vector<pixel> expand(std::vector<pixel> v){
    std::vector<pixel> v1;
    pixel X1, X2;
    X2=v.data()[v.size()-1];
    int x=X2.getX();
    int y=X2.getY();
    for(int i=0;i<(int)v.size();i++){
        X1=X2;
        X2=v.data()[i];
        while(x!=X2.getX()&&y!=X2.getY()){
            v1.push_back(pixel(x,y));
            if (f(x,y+1,X1,X2)>0&&f(x,y,X1,X2)>=0)
                    y-=1;
            else if (f(x,y+1,X1,X2)<0&&f(x,y,X1,X2)<=0)
                    y+=1;
            else if (f(x+1,y,X1, X2)>0&&f(x,y,X1,X2)>=0)
                    x-=1;
            else if (f(x+1,y,X1, X2)<0&&f(x,y,X1,X2)<=0)
                    x+=1;
        }
    }
    return v1;
}

/*
void test_frontiere(int argc, char* argv[],frontiere f){
    Imagine::Image<pixel> I1(100,200);  //Image I1
    getImage(I1,srcPath("pictures/baby.png"),argc,argv);
    affiche(I1,1);
    std::vector<pixel> v;
    initialize_frontiere(I1,v);
    f.initialize_frontiere(v);
    std::list<pixel>::iterator it;
    for (it=f.begin();it!=f.end();++it){
        drawPoint((*it).getX(),(*it).getY(),BLACK);
    }
    int x,y;
    getMouse(x,y);

    std::vector<pixel> v1=frontiere_tampon(I1,x,y,30);
    int s=v1.size();
    for (int i=0;i<s;i++){
        drawPoint(v1[i].getX(),v1[i].getY(),RED);
    }
    f.pop_frontiere(v1);

    f.add_frontiere_initialise(v1,I1);

    for (it=f.begin();it!=f.end();++it){
        drawPoint((*it).getX(),(*it).getY(),WHITE);
    }

    click();

    for (int i=1;i<60;i++){
        for (int j=1;j<60;j++){
            I1(x-30+i,y-30+j).setV(1);
        }
    }
    getMouse(x,y);

    std::vector<pixel> v2=frontiere_tampon(I1,x,y,30);
    int s2=v2.size();
    for (int i=0;i<s;i++){
        drawPoint(v2[i].getX(),v2[i].getY(),RED);
    }
    f.pop_frontiere(v2);

    f.add_frontiere(v2,I1);

    for (int i=1;i<60;i++){
        for (int j=1;j<60;j++){
            I1(x-30+i,y-30+j).setV(1);
        }
    }
    getMouse(x,y);

    std::vector<pixel> v3=frontiere_tampon(I1,x,y,30);
    int s3=v3.size();
    for (int i=0;i<s;i++){
        drawPoint(v3[i].getX(),v3[i].getY(),RED);
    }
    f.pop_frontiere(v3);

    f.add_frontiere(v3,I1);
    for (it=f.begin();it!=f.end();++it){
        drawPoint((*it).getX(),(*it).getY(),BLUE);
    }
    for (int i=1;i<60;i++){
        for (int j=1;j<60;j++){
            I1(x-30+i,y-30+j).setV(1);
        }
    }
    getMouse(x,y);
    std::vector<pixel> v4=frontiere_tampon(I1,x,y,30);
    int s4=v4.size();
    for (int i=0;i<s4;i++){
        drawPoint(v4[i].getX(),v4[i].getY(),RED);
    }
    f.pop_frontiere(v4);

    f.add_frontiere(v4,I1);
    for (it=f.begin();it!=f.end();++it){
        drawPoint((*it).getX(),(*it).getY(),WHITE);
    }
    click();

}
*/


void testMatching1(int argc, char* argv[]){
    initRandom();
    Imagine::Image<pixel> I1(100,200);  //Image I1
    getImage(I1,srcPath("pictures/apple.png"),argc,argv);
    affiche(I1,1);
    click();
    pixel testpixel(rand()%(I1.width()-40)+20,I1.height()/2);
    fillCircle(testpixel.getX(),testpixel.getY(),3,RED);
    int sizeTamp=20;
    drawRect(testpixel.getX()-sizeTamp,testpixel.getY()-sizeTamp,2*sizeTamp+1,2*sizeTamp+1,RED);
    click();
    Imagine::FVector<int,2> goodMatch(0,0);
    matching1(goodMatch.x(),goodMatch.y(),I1,testpixel.getX(),testpixel.getY(),sizeTamp);
    std::cout<<"x="<<goodMatch.x()<<", y="<<goodMatch.y()<<std::endl;
    fillCircle(goodMatch.x(),goodMatch.y(),3,BLUE);
    drawRect(goodMatch.x()-sizeTamp,goodMatch.y()-sizeTamp,2*sizeTamp+1,2*sizeTamp+1,BLUE);
    endGraphics();
}

void testMatching2(int argc, char* argv[]){
    initRandom();
    Imagine::Image<pixel> I1(100,200);  //Image I1
    getImage(I1,srcPath("baby.png"),argc,argv);
    affiche(I1,1);
    /*
    click();
    pixel testpixel(rand()%(I1.width()-40)+20,rand()%(I1.height()-40)+20);
    drawPoint(testpixel.getX(),testpixel.getY(),RED);
    */

    int clickX, clickY;
    getMouse(clickX, clickY);
    pixel testpixel(clickX,clickY);

    int sizeTamp=10;

    for(int i=testpixel.getX()-2*sizeTamp;i<=testpixel.getX()+2*sizeTamp;i++){
        for(int j=testpixel.getY()+1;j<=testpixel.getY()+2*sizeTamp;j++){
            I1(i,j).setV(0);
            drawPoint(i,j,WHITE);
        }
    }

    drawRect(testpixel.getX()-sizeTamp,testpixel.getY()-sizeTamp,2*sizeTamp,2*sizeTamp,RED);
    click();
    Imagine::FVector<int,2> goodMatch(0,0);
    int distanceMin=matching2(goodMatch.x(),goodMatch.y(),I1,testpixel.getX(),testpixel.getY(),sizeTamp);
    std::cout<<"x="<<goodMatch.x()<<", y="<<goodMatch.y()<<"Distance du tampon à la source :"<<distanceMin<<std::endl;
    drawPoint(goodMatch.x(),goodMatch.y(),BLUE);
    drawRect(goodMatch.x()-sizeTamp,goodMatch.y()-sizeTamp,2*sizeTamp,2*sizeTamp,CYAN);

    /*
    std::cout<<(I1[testpixel.getX(),testpixel.getY()].getColor().r(), I1[testpixel.getX(),testpixel.getY()].getColor().g(),I1[testpixel.getX(),testpixel.getY()].getColor().b())<<std::endl;
    I1(testpixel.getX()-5,testpixel.getY()-5);
    std::cout<<int(I1[testpixel.getX()-5,testpixel.getY()-5].getColor().r())<<std::endl;
    const Color testcol(int(I1[testpixel.getX()-5,testpixel.getY()-5].getColor().r()), int(I1[testpixel.getX()-5,testpixel.getY()-5].getColor().g()),int(I1[testpixel.getX()-5,testpixel.getY()-5].getColor().b())) ;
    const Color uwu(200,100,50);
    std::cout<<testcol<<std::endl;
    fillRect(testpixel.getX()-20,testpixel.getY()-20,10,10,uwu);
    */

    endGraphics();
}
int min(int x,int y){
    if (x<y)
        return x;
    return y;
}

int max(int x, int y){
    if (x>y)
        return x;
    return y;
}

//FONCTION A DEFINIR (explication quant à leur objectif en commentaire de pseudoMain()
bool selectZone(int& x1,int& y1,int& x2,int& y2){
    return(getMouse(x1, y1)==1 && getMouse(x2,y2)==1);
    /* demande deux clics gauches, remplit x1, y1, x2 et y2 avec les coordonnées des clics et retourne True
     * En cas de clic droit, retourne False
     */
}

bool endCondition(frontiere f, Imagine::Image<pixel> I){
    return f.isVoid();
    // A completer
    /* La condition de fin est : 1- la frontière est vide ; 2- la frontière est réduite au bord de l'image
     */
}

void copyTampon(int Px, int Py, int Qx, int Qy, Imagine::Image<pixel> I, int tailleTampon){
    //Copie les couleurs de la zone source à la zone copiée (lorsque leur v=0) ET passe leur v à 1 (visité)
    for(int i=-tailleTampon; i<=tailleTampon; i++){                 // on parcourt le tampon autour du pixel P
        for(int j=-tailleTampon; j<=tailleTampon; j++){
            if (not I(Px+i,Py+j).getV()){                           // si le pixel P n'a pas encore été visité,
                I(Px+i,Py+j).setColor(I(Qx+i,Qy+j).getColor());     // on copie la couleur de Q
                I(Px+i,Py+j).setV(true);                            // et on passe P en visité
            }
        }
    }
}
//
int minBord(int a, int b, int c, int d){    //Renvoie le minimum de 4 entier (utilisé pour le cas où le tampon est inférieur au bord
    int min = a;
    if (min>b)
        min=b;
    if (min>c)
        min=c;
    if (min>d)
        min=d;
    return min;

}
void PseudoMain(int argc,char* argv[]){

    //ETAPE 1 : Initialisation des variables, de l'image et de la frontière

    int zoom=1;                                         //Variable zoom qui permettra d'agrandir l'image (on adaptera les fonctions si on a le temps à la fin)
    Imagine::Image<pixel> I1(100,200);                  //Déclaration de l'image 1
    getImage(I1,srcPath("pictures/landscape.png"),argc,argv);    //Lecture de l'image "landscape.png"
    openWindow(I1.width()*zoom, I1.height()*zoom);;
    affiche(I1,zoom);                                   //Affichage de l'image
    int x1=0,x2=0,y1=0,y2=0;
    //(A ECRIRE : bool selectZone(x1,y1,x2,y2) )   //Fonction demandant à l'utilisateur de clique-gauche 2 fois et renvoyant dans
    while (!selectZone(x1,y1,x2,y2)){              //x1, y1, x2 et y2 les coordonnées des clicks correspondant et True via le return
    }                                                   //Renvoie false si un click droit est pressé
                                                        //NB : le code ci-dessus force l'utilisateur à sélectionner au moins une zone
    std::vector<pixel> v(0);                            //Vecteur qui contiendra les pixels des zones selectionnés par l'utilisateur
    initialize_frontiere(I1,v,x1,y1,x2,y2);             //Initialise la frontière à partir des coordonnées des points
                                                        //(NB : la frontière étant consituée pixels étant remplit, seul les pixels STRICTEMENT
                                                        //      dans le rectangle sont effacés)
    noRefreshBegin();                                   //Permettra de gagner du temps de calcul
    for (int i=min(x1,x2)+1;i<max(x1,x2);i++){
        for (int j=min(y1,y2)+1;j<max(y1,y2);j++){
            drawPoint(i,j,WHITE);                       //Dessine le pixel en blanc sur l'affichage
            I1(i,j).setColor(WHITE);                    //Remplace la couleur du pixel par blanc
            I1(i,j).setV(0);                            //Met le pixel sur "non visité"
            I1(i,j).setConfidence(0);                   //Met la confiance du pixel à 0
        }
    }
    noRefreshEnd();                                     //Met à jour l'affichage
    frontiere f;                                        //Frontière de l'image "pleine" avec les parties vides
    f.initialize_frontiere(v);                          //Initialisation de f
    while(selectZone(x1,y1,x2,y2)){
        v.clear();                                      //Vide le vecteur

        initialize_frontiere(I1,v,x1,y1,x2,y2);         //Code précédent
        noRefreshBegin();
        for (int i=min(x1,x2)+1;i<max(x1,x2);i++){
            for (int j=min(y1,y2)+1;j<max(y1,y2);j++){
                drawPoint(i,j,WHITE);
                I1(i,j).setColor(WHITE);
                I1(i,j).setV(0);
            }
        }
        noRefreshEnd();                                     //Met à jour l'affichage

        f.add_frontiere_initialise(v,I1);                   //Adapte f au nouveau contour
    }

    f.changeData(I1);

    //L'image et la frontière sont à ce moment initialisé

<<<<<<< HEAD
    int tailleTampon=3;                                //valeur caractérisant la taille du tampon (modifiable)
=======
    int tailleTampon=8;                                //valeur caractérisant la taille du tampon (modifiable)
    int savetailleTampon=tailleTampon;                 // Sera utilisé pour retrouver la valeur initiale du tampon
>>>>>>> 502add78e2924e92a18e0715098ae182a401df4c

    //ETAPE 2 : Boucle de remplissage de l'image

    //La condition de fin est : 1- la frontière est vide ; 2- la frontière est réduite au bord de l'image
    //De plus, si le tampon "dépasse" l'image, la fonction matching2 ne marchera pas (out of index), il faudra donc adapter le tampon
    while(!endCondition(f,I1)) {                            //Fonction à définir selon les conditions plus haut

        //PARTIE CALCUL DE LA DATA (de la frontière) (Wandrille je te laisse faire)

        //NOTE POUR TOUT LE MONDE : Il me semble que pour le terme de confiance, celui-ci est effectivement update pour les element nouvellement
        //                          copié par le tampon depuis le pixel source. Cependant, les pixels faisant parti de la frontière fois ensuite
        //                          leur confiance recalculé par la formule donnée (qui fait une "moyenne des confiance environnante"). Il ne me
        //                          semble pas que nous ayons écrit une méthode faisant cette Update à partir de la formule.

        //A partir de là, la confiance et la data de chacun des termes de la frontière a été défini
        pixel Pmax=f.max_priority();                        //P est le pixel de priorité maximale dans la frontière
        int Qx=-1, Qy=-1;                                   //(Qx, Qy) sera le pixel source de notre algorithme
        if ((tailleTampon<=Pmax.getX()) && (Pmax.getX()<(I1.width()-1)-tailleTampon) && (tailleTampon<=Pmax.getY()) && (Pmax.getY()<(I1.height()-1)-tailleTampon) ){
            //EXPLICATION DE LA CONDITION CI-DESSUS : Le tampon, qui sera la zone qui sera recopiée autour de Pmax, doit nécessairement être
            //                                        contenue dans l'image (sinon matching2 ne marche pas). Pour cela, on adapte la taille
            //                                        du tampon. la condition ci-dessus est satisfaite ssi le tampon est dans l'image
            //                                        (les pixels remplis par le tampon vont de Pmax à ses tailleTampon pixels environant (norme inf),
            //                                         il faut donc que Pmax soit à tous moments à tailleTampon+1 (inclu) du bord (donc entre
            //                                         index tailleTampon et index (indexMax-(tailleTampon+1))) (NB : l'index commence à 0)

            matching2(Qx,Qy,I1,Pmax.getX(),Pmax.getY(),tailleTampon); //Recherche du meilleur pixel source (Qx,Qy) dans l'image
            compute_and_changeConfidence(I1,Pmax,tailleTampon);                 //Copie le terme C de Pmax dans les pixels qui seront re
            copyTampon(Pmax.getX(), Pmax.getY(), Qx, Qy, I1, tailleTampon); //Copie les couleurs de la zone source à la zone copiée (lorsque leur v=0) ET passe leur v à 1 (visité)
            affiche(I1,zoom);                                         //Affiche l'image modifié (nb : les pixels des zones "vides" ont été changé en blanc lors de leur sélection)
            std::vector<pixel> v1=frontiere_tampon(I1,Pmax.getX(),Pmax.getY(),tailleTampon);        //Une "nouvelle frontière" est crée, celle entourant la zone nouvellement copiée (ce n'est en réalité qu'une liste de pixel potentiel à la frontière
            f.pop_frontiere(v1);                                      //Suppression des éléments à l'intérieur du tampon
            f.add_frontiere(v1,I1);                                   //Ajout de la nouvelle frontière
            f.changeData(I1);
        }
        else {
            tailleTampon=minBord(Pmax.getX(), Pmax.getY(), abs(I1.width()-1-Pmax.getX()), abs(I1.height()-1-Pmax.getY()));  //Le tampon prend comme taille la distance la plus courte jusqu'au bord (pour pouvoir appliquer matching sans problème)

            matching2(Qx,Qy,I1,Pmax.getX(),Pmax.getY(),tailleTampon); //Recherche du meilleur pixel source (Qx,Qy) dans l'image
            compute_and_changeConfidence(I1,Pmax,tailleTampon);                 //Copie le terme C de Pmax dans les pixels qui seront re
            copyTampon(Pmax.getX(), Pmax.getY(), Qx, Qy, I1, tailleTampon); //Copie les couleurs de la zone source à la zone copiée (lorsque leur v=0) ET passe leur v à 1 (visité)
            affiche(I1,zoom);                                         //Affiche l'image modifié (nb : les pixels des zones "vides" ont été changé en blanc lors de leur sélection)
            std::vector<pixel> v1=frontiere_tampon(I1,Pmax.getX(),Pmax.getY(),tailleTampon);        //Une "nouvelle frontière" est crée, celle entourant la zone nouvellement copiée (ce n'est en réalité qu'une liste de pixel potentiel à la frontière
            f.pop_frontiere(v1);                                      //Suppression des éléments à l'intérieur du tampon
            f.add_frontiere(v1,I1);                                   //Ajout de la nouvelle frontière
            f.changeData(I1);

            tailleTampon=savetailleTampon;  //On redonne la valeur initiale au tampon

        }
    }
    endGraphics();
}

int main(int argc, char* argv[]) {
    //testMatching2(argc,argv);
    PseudoMain(argc,argv);
	return 0;
}
