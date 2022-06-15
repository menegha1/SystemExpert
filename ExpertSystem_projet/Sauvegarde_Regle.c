#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sauvegarder_regle.h"

/*
Cette fonction va permettre d'�crire dans un fichier ( text.txt )  la liste contenant toutes les r�gles avec
la liste de pr�misse et conclusion ( Liste_baseco)

*/
void save_liste(Liste_baseco x)
{
    FILE* f = NULL;

    f = fopen("test.txt", "w"); // on ouvre l'acc�s au fichier " text.txt " en mode �criture

    if (f != NULL) // on v�rifie si le fichier est bien ouvert
    {
        if (x == NULL) // v�rification si la liste base_co est vide ou non
        {
            printf(" \n la liste de r�gle est vide \n" );// si oui , alors on �crit dans la console est vide , cependant on �crira rien dans le fjichier  pour �viter les probl�mes lors de la lecture du fichier
        }
        else
        {
            Liste_baseco p =  x ;// on cr�e un pointeur de la liste de r�gle

            while (p!= NULL)
                //on effectue la boucle jusqu'au dernier �lement de la liste de r�gle,
            //on �crira dans le fichier  chaque regle qui seront dissoci�s par un " \n "
            {
                if(p->l2 == NULL  || p->nom =="\n")
                // on v�rifie si la liste  de premisse n'est pas nul , et si le nom de la r�gle n'est pas " \n " afin d'�viter
                // les sauts de lignes en trop dans le fichier
                {

                }
                else
                {
                    fprintf(f,"%s|",p->nom);
                    // on �crit dans un premier temps le nom de la r�gle dans le fichier , qu'on s�parera du reste avec " | "
                    // afin de faciliter la lecture du fichier

                    Regle * l = p->l2;
                    while (l->next != NULL)
                        // on �crit chaque premisse  pour chaque r�gle , on s�parera chaque proposition par une virgule
                        // afin de faciliter la lecture du fichier
                    {
                        fprintf(f, "%s,", l->prop);
                        l = l->next;
                    }
                    fprintf(f, "%s", l->prop);// on �crira en dernier la conclusion ( qui n'aura pas de virgule  � la fin
                    p = p->next;
                }
            }

        }
        fclose(f);// on ferme le fichier " text.txt " qu'on avait ouvert


    }else{
    printf(" Il y a eu un probleme lors de l'ouverture du fichier ");
    }
}

/*Cette fonction va permettre la lecture du fichier( text.txt ) afin de r�cup�rer la liste contenant toutes les r�gles avec
la liste de pr�misse et conclusion ( Liste_baseco)
*/
Liste_baseco load_liste(Liste_baseco x )
{
    FILE* f = NULL;

    char boucle[1000] ="";
// on cr�e des cha�nes de caract�res en pointeurs  qu'on utilisera dans la fonction
    char * t ;
    char *c ;
    char *m ;

    f = fopen("test.txt", "r");// on ouvre l'acc�s au fichier " text.txt " en mode lecture



    if (f != NULL)// De la m�me fa�on que la fonction pr�c�dente, on v�rfie  si le fichier a bien �t� ouvert
    {
        while(fgets(boucle,1000,f)!= NULL)
            //on effectue une boucle , qui nous permettra de lire chaque ligne du fichier jusqu'� la derni�re ligne inclus
            //pour ce faire on effectue la fonction fgets, qui va nous permettre de r�cuperer  une ligne enti�re ,
            // soit une cha�ne de caract�re jusqu'� ce qu'il rencontre un " \n", qu'on assignera � la cha�ne de caract�re " boucle"
            //chaque boucle effectu� repr�sentera une r�gle
        {

            //on alloue la m�moire suffisante aux deux cha�nes de caract�re
            t = (char *)malloc(50*sizeof(char));
            m = (char *)malloc(50 * sizeof(char));

            Liste_regle l = NULL;// on cr�e un nouvelle liste de pr�misse

            t = strtok(boucle,"|");
            //on effectue le premier strtok( ainsi on founrit la cha�ne de caract�re � d�couper) ,  qui nous permettra d'extraire tous les �lements de la cha�ne de caract�re " boucle ",
            //jusqu'au s�parateur qu'on aura indiquer , soit " | " dans le cas pr�sent.
            strcpy ( m,t );
            //on copie la premi�re cha�ne de caract�re extraite dans la cha�ne de caract�re " m " afin de la stocker( qui repr�sente le nom de la r�gle)
            t = strtok(NULL,",");
            // c'est le deuxi�me strtok , de ce fait on founri un pointeur NULL et non la cha�ne � d�couper
            //on extrait la cha�ne de caract�re jusqu'� la premi�re virgule ( la premi�re premisse)
            while(t != NULL)//on effectue une boucle jusqu'� ce que la cha�ne de caract�re extraite avec strtok soit NULL
            {
                c =(char*)malloc(50*sizeof(char));// on alloue la m�moire suffisante pour la cha�ne de caract�re " c "
                strcpy(c,t);//on copie la cha�ne de caract�re extraite dans la cha�ne de caract�re " c "
                l = insert_proposition(l,c);// on ins�re ensuite cette cha�ne de caract�re dans une liste de premisse

                t = strtok(NULL,",");//on extrait de nouveau la cha�ne de caracti�re jusqu'� la prochaine virgule ( qui repr�sentera une proposition )

            }
            x = insert_regle_predefini(x,l,m);
            //on insere la regle qu'on aura extraite du fichier dans la liste base_co , avec le nom de le r�gle ( soit " m" )
            // et la liste  l  ( soit la liste de premisse avec la conclusion � la fin )
        }

    }else{
    printf(" Il y a eu un probleme lors de l'ouverture du fichier");
    }


    fclose(f);// on ferme le fichier " text.txt " qu'on avait ouvert



    return x;

}
