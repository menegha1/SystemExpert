#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sauvegarder_regle.h"

/*
Cette fonction va permettre d'écrire dans un fichier ( text.txt )  la liste contenant toutes les règles avec
la liste de prémisse et conclusion ( Liste_baseco)

*/
void save_liste(Liste_baseco x)
{
    FILE* f = NULL;

    f = fopen("test.txt", "w"); // on ouvre l'accès au fichier " text.txt " en mode écriture

    if (f != NULL) // on vérifie si le fichier est bien ouvert
    {
        if (x == NULL) // vérification si la liste base_co est vide ou non
        {
            printf(" \n la liste de règle est vide \n" );// si oui , alors on écrit dans la console est vide , cependant on écrira rien dans le fjichier  pour éviter les problèmes lors de la lecture du fichier
        }
        else
        {
            Liste_baseco p =  x ;// on crée un pointeur de la liste de règle

            while (p!= NULL)
                //on effectue la boucle jusqu'au dernier élement de la liste de règle,
            //on écrira dans le fichier  chaque regle qui seront dissociés par un " \n "
            {
                if(p->l2 == NULL  || p->nom =="\n")
                // on vérifie si la liste  de premisse n'est pas nul , et si le nom de la règle n'est pas " \n " afin d'éviter
                // les sauts de lignes en trop dans le fichier
                {

                }
                else
                {
                    fprintf(f,"%s|",p->nom);
                    // on écrit dans un premier temps le nom de la règle dans le fichier , qu'on séparera du reste avec " | "
                    // afin de faciliter la lecture du fichier

                    Regle * l = p->l2;
                    while (l->next != NULL)
                        // on écrit chaque premisse  pour chaque règle , on séparera chaque proposition par une virgule
                        // afin de faciliter la lecture du fichier
                    {
                        fprintf(f, "%s,", l->prop);
                        l = l->next;
                    }
                    fprintf(f, "%s", l->prop);// on écrira en dernier la conclusion ( qui n'aura pas de virgule  à la fin
                    p = p->next;
                }
            }

        }
        fclose(f);// on ferme le fichier " text.txt " qu'on avait ouvert


    }else{
    printf(" Il y a eu un probleme lors de l'ouverture du fichier ");
    }
}

/*Cette fonction va permettre la lecture du fichier( text.txt ) afin de récupérer la liste contenant toutes les règles avec
la liste de prémisse et conclusion ( Liste_baseco)
*/
Liste_baseco load_liste(Liste_baseco x )
{
    FILE* f = NULL;

    char boucle[1000] ="";
// on crée des chaînes de caractères en pointeurs  qu'on utilisera dans la fonction
    char * t ;
    char *c ;
    char *m ;

    f = fopen("test.txt", "r");// on ouvre l'accès au fichier " text.txt " en mode lecture



    if (f != NULL)// De la même façon que la fonction précédente, on vérfie  si le fichier a bien été ouvert
    {
        while(fgets(boucle,1000,f)!= NULL)
            //on effectue une boucle , qui nous permettra de lire chaque ligne du fichier jusqu'à la dernière ligne inclus
            //pour ce faire on effectue la fonction fgets, qui va nous permettre de récuperer  une ligne entière ,
            // soit une chaîne de caractère jusqu'à ce qu'il rencontre un " \n", qu'on assignera à la chaîne de caractère " boucle"
            //chaque boucle effectué représentera une règle
        {

            //on alloue la mémoire suffisante aux deux chaînes de caractère
            t = (char *)malloc(50*sizeof(char));
            m = (char *)malloc(50 * sizeof(char));

            Liste_regle l = NULL;// on crée un nouvelle liste de prémisse

            t = strtok(boucle,"|");
            //on effectue le premier strtok( ainsi on founrit la chaîne de caractère à découper) ,  qui nous permettra d'extraire tous les élements de la chaîne de caractère " boucle ",
            //jusqu'au séparateur qu'on aura indiquer , soit " | " dans le cas présent.
            strcpy ( m,t );
            //on copie la première chaîne de caractère extraite dans la chaîne de caractère " m " afin de la stocker( qui représente le nom de la règle)
            t = strtok(NULL,",");
            // c'est le deuxième strtok , de ce fait on founri un pointeur NULL et non la chaîne à découper
            //on extrait la chaîne de caractère jusqu'à la première virgule ( la première premisse)
            while(t != NULL)//on effectue une boucle jusqu'à ce que la chaîne de caractère extraite avec strtok soit NULL
            {
                c =(char*)malloc(50*sizeof(char));// on alloue la mémoire suffisante pour la chaîne de caractère " c "
                strcpy(c,t);//on copie la chaîne de caractère extraite dans la chaîne de caractère " c "
                l = insert_proposition(l,c);// on insère ensuite cette chaîne de caractère dans une liste de premisse

                t = strtok(NULL,",");//on extrait de nouveau la chaîne de caractière jusqu'à la prochaine virgule ( qui représentera une proposition )

            }
            x = insert_regle_predefini(x,l,m);
            //on insere la regle qu'on aura extraite du fichier dans la liste base_co , avec le nom de le règle ( soit " m" )
            // et la liste  l  ( soit la liste de premisse avec la conclusion à la fin )
        }

    }else{
    printf(" Il y a eu un probleme lors de l'ouverture du fichier");
    }


    fclose(f);// on ferme le fichier " text.txt " qu'on avait ouvert



    return x;

}
