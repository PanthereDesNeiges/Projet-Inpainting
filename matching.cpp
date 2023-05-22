#include "matching.h"
#include <queue>

void matching1(int& Qx, int& Qy, Imagine::Image<pixel> I, int Px, int Py, int n){
    /* Principe : La fonction cherche les coordonnées d'un pixel Q dont le carré Psy_Q (carré de coté 2n+1 centré en Q) "match"
     *            avec Psy_P. Le choix du pixel Q dans le cas où il y a plusieurs matching sera arbitraire).
     *            Les coordonnées de Q seront passés à Qx et Qy. P a pour coordonné Px et Py. On travaille sur l'image I.
     *            Dans le cas où aucun matching n'est trouvé, la fonction renvoira une erreur.
     *
     *            ATTENTION A DECALER QUAND ON COPIE (la fonction copie prend le pixel en haut à gauche, la mienne donne le pixel du centre
     */
    int h=I.height(), w=I.width();
    bool flag;                                //Sera utile pour indiquer si un pixel est entier ou pas

    Imagine::Image<bool> filled(w,h);         //Stock l'image représentant les cases remplis/pas remplis
    getFilledMap(I, filled);                  //Initialisation de filled

    std::queue<int> ListQx;                   //On va stocker les pixels candidats à Q (pixel q tel que Psy_q est "plein" (le tampon))
    std::queue<int> ListQy;                   //Le choix d'une file est arbitraire (une pile aurait été équivalente)

    for (int i=n;i<w-n-1;i++){
        for (int j=n; j<h-n-1;j++){           // Les sample potentiels sont ceux de coordonné (i,j). Au dela de ces valeurs, Psy_q n'est plus carré
            flag=true;                        // Cherchons les q potentiel (ceux dont Psy_q est "plein")

            for (int k=-n;k<=n;k++){
                for (int l=-n;l<=n;l++){
                    if(not filled(i+k,j+l)){
                        flag=false;           // Si un des pixels environnants est non rempli, on passe le flag à "faux"
                        break;                // Sortie des boucles
                    }
                }
                if (not flag)                 // Si un des pixels environnants est non rempli (flag false)
                    break;                    // Sortie des boucles
            }
            if (flag){                        // Si aucun pixel environnant est vide
                ListQx.push(i);
                ListQy.push(j);
            }
        }
    }
    assert(not ListQx.empty()); // La liste ne doit pas être vide
    // On a maintenant dans la queue tous les point x de phi tel que Psy_phy soit plein. On peut chercher parmi ceux ci lequel match avec le patern de Psy_p
    int x,y;
    int InitSize=ListQx.size();
    for(int m=0;m<InitSize;m++){ //Tant que la liste n'est pas vide
        flag=true;
        x=ListQx.front();
        y=ListQy.front();
        ListQx.pop();
        ListQy.pop();
        for(int k=-n;k<=n;k++){
            for(int l=-n;l<=n;l++){     // On regarde les pixels avoisinant
                if (filled(Px+k,Py+l) and I(x+k,y+l).getColor() != I(Px+k,Py+l).getColor()){  //Si un des pixels avoisinant ne match pas (la première condition vérifie qu'on vérifie seulement dans Phi)
                    flag=false;
                    break;
                }
            }
            if (not flag)
                break;          //Sortie des boucles
        }
        if (flag){              //Le pixel en (x,y) convient
            Qx=x, Qy=y;
            return;
        }
    }
    Qx=-1, Qy=-1; // Aucun pixel trouvé
    std::cout<<"No matching found for pixel ("<<Px<<","<<Py<<")"<<std::endl;
}

int dist1tampon(int x, int y, int xc, int yc, int n, Imagine::Image<pixel> I, Imagine::Image<bool> filled){ //renvoie la distance induite par la norme 1 sur les tampons
    int dist=0;

    //std::cout<<"xc="<<xc<<", yc="<<yc<<", x="<<x<<", y"<<y<<std::endl;

    for (int k=-n;k<=n;k++){
        for (int l=-n;l<=n;l++){
            if(filled(xc+k,yc+l)){

                //drawPoint(xc+k,yc+l,BLUE);
                //drawPoint(x+k,y+l,ORANGE);
                //std::cout<<I(x+k,y+l).getColor()<<", "<<I(xc+k,yc+l).getColor()<<std::endl;

                dist+=abs(int(I(x+k,y+l).getColor().r())-int(I(xc+k,yc+l).getColor().r()))+abs(int(I(x+k,y+l).getColor().g())-int(I(xc+k,yc+l).getColor().g()))+abs(int(I(x+k,y+l).getColor().b())-int(I(xc+k,yc+l).getColor().b()));
            }
        }
    }
    return dist;
}

int matching2(int& Qx, int& Qy, Imagine::Image<pixel> I, int Px, int Py, int n){ //Cherche le meilleur matching du tampon en (Px,Py)
    int h=I.height(), w=I.width();
    bool flag;                                //Sera utile pour casser la boucle dans le cas où un matching parfait est trouvé
    Imagine::Image<bool> filled(w,h);         //Carte des pixels déjà remplis (bool=1)
    getFilledMap(I, filled);
    std::queue<int> ListQx;                   //On va stocker les pixels candidats à Q (pixel q tel que Psy_q est "plein".
    std::queue<int> ListQy;                    //Le choix d'une file est arbitraire (une pile aurait été équivalente)
    for (int i=n;i<w-n-1;i++){
        for (int j=n; j<h-n-1;j++){      // Les sample potentiels sont ceux de coordonné (i,j). Au dela de ces valeurs, Psy_q n'est plus carré
            flag=true;                   // Cherchons les q potentiel (ceux dont Psy_q est "plein")
            for (int k=-n;k<=n;k++){
                for (int l=-n;l<=n;l++){
                    if(not filled(i+k,j+l)){
                        flag=false;
                        break;           //Sortie des boucles
                    }
                }
                if (not flag)
                    break;
            }
            if (flag){
                ListQx.push(i);
                ListQy.push(j);
            }
        }
    }
    //On a désormait la liste des pixels potentiels, il faut calculer leur distance pour trouver le meilleur matching
    assert(not ListQx.empty()); // La liste ne doit pas être vide
    int x,y,dist;
    int minDist=dist1tampon(ListQx.front(),ListQy.front(),Px,Py,n, I, filled);
    Qx=ListQx.front();
    Qy=ListQy.front();
    ListQx.pop();
    ListQy.pop();
    int InitSize=ListQx.size();
    for(int m=0;m<InitSize;m++){ //Tant que la liste n'est pas vide
        x=ListQx.front();
        y=ListQy.front();
        ListQx.pop();
        ListQy.pop();

        //std::cout<<"r()="<<int(I(x,y).getColor().g())<<", [red]="<<I(x,y).getColor().g()<<", color="<<I(x,y).getColor()<<std::endl;

        dist=dist1tampon(x,y,Px,Py,n,I,filled);

        //std::cout<<dist<<std::endl;

        if (dist<=minDist){
            Qx=x;
            Qy=y;
            minDist=dist;
            if(dist==0){    //cas matching optimal
                std::cout<<"Perfect match!"<<std::endl;
                return 0;
            }
        }
    }
    return minDist;
}
