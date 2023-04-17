#include "matching.h"
#include <queue>
/* OBJECTIF : Coder une fonction qui trouve des exemples dans Phi (figure 2) du pattern déjà présent dans Psy_p
 *
 * pb : Que faire s'il n'y a aucun matching ? Plusieurs matching ?
 */

void matching1(int& Qx, int& Qy, Imagine::Image<pixel> I, int Px, int Py, int n){
    /* Principe : La fonction cherche les coordonnées d'un pixel Q dont le carré Psy_Q (carré de coté 2n+1 centré en Q) "match"
     *            avec Psy_P. Le choix du pixel Q dans le cas où il y a plusieurs matching sera arbitraire).
     *            Les coordonnées de Q seront passés à Qx et Qy. P a pour coordonné Px et Py. On travaille sur l'image I.
     *            Dans le cas où aucun matching n'est trouvé, la fonction renvoira une erreur.
     *
     *            ATTENTION A DECALER QUAND ON COPIE (la fonction copie prend le pixel en haut à gauche, la mienne donne le pixel du centre
     */
    int h=I.height(), w=I.width();
    bool flag;

    Imagine::Image<bool> filled(w,h);         //Stock l'image représentant les cases remplis/pas remplis
    getFilledMap(I, filled);

    std::queue<int> ListQx;              //On va stocker les pixels candidats à Q (pixel q tel que Psy_q est "plein".
    std::queue<int> ListQy;              //Le choix d'une file est arbitraire (une pile aurait été équivalente)

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

void matching2(int& Qx, int& Qy, Imagine::Image<pixel> I, int Px, int Py, int n); //Cherche le meilleur matching du tampon en (Px,Py)
