#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction_List.h"

int count_normal(Liste_regle  list)     /*Permet de compter le nombre de valeur contenu dans une liste*/
{
    int nb = 0;
    Regle * p =  list ;
    if( p == NULL )
    {
        return nb;
    }
    else
    {
        while (p->next != NULL)
        {
            p = p->next;
            nb++;
        }

        return nb;
    }

}

int search_Val(Liste_regle list,char * e)   /*Cherche si une valeur est d�j� pr�sente dans une liste (le programme ne parcours pas la derni�re valeur (qui est la conclusion) et c'est une fonction RECURSIVE*/
{

    if( list ->next == NULL)  /*==> Diff�rence avec search_Valconclu()*/
    {
        return 1;   /*1 == Non il n'y a pas de valeur similaire dans la liste*/
    }
    if( list == NULL)
    {
        return 1 ;
    }
    else
    {
        if (strcmp(list->prop,e)==0)    /* Le caract�re prop(list) est similaire au caract�re e*/
        {
            return 0; /*0 == Oui il y a une valeur similaire dans la liste*/
        }
    }
    return search_Val(list->next,e);
}
int search_Valconclu(Liste_regle list,char * e)     /*M�me fonction que search_val() mais la comparaison se fait dans tout la liste (m�me le dernier caract�re de la liste) et la fonction est RECURSIVE*/
{
    int cont=1;
    if( list == NULL)   /*==> Diff�rence avec search_val()*/
    {
        return 1 ;
    }
    else
    {
        if (strcmp(list->prop,e)==0)
        {
            return 0;
        }
    }
    return search_Valconclu(list->next,e);
}

Liste_baseco supprimerListe( Liste_baseco ancienneBaseCo  )     /*Fonction permettant de supprimer une regle premis les base de connaissance*/
{

    char * c ;//on cr�e une cha�ne de caract�r en pointeur
    c = (char*) malloc(100 * sizeof(char));//on alloue la m�more suffisantes pour la cha�ne de caract�re
    Base_co * p = ancienneBaseCo ; // on cr�e un pointeur de la base_co actuelle

    printf(" \nQuel est le nom de la recette (exemple : pizza-italienne) a supprimer :  ");
    scanf("%s",c);//on lit une  cha�ne de caract�re, soit le nom de la recette qu'on souhaite supprimer

    if (ancienneBaseCo == NULL)// on verifi si la base_co n'est pas vide
    {
        printf(" La liste de r�gle est vide \n \n");
        return NULL;// si oui , alors on finit  la fonction
    }
    else
    {
        if (strcmp(p->nom,c)== 0 )// on v�rifie si la cha�ne de caract�re saisit correspond  au nom de la recette de la premi�re regle
        {
            //si oui,  on v�rifie alors si il existe une prochaine r�gle
            if (p->next == NULL )
            {
                //si  la liste comprend qu'une seul r�gle alors on lib�re la liste actuelle
                free(p);
                return ancienneBaseCo;
            }
            else
            {
                //si il existe d'autres r�gles , alors on cr�e un pointeur qui va pointer sur la prochaine r�gle la liste actuelle
                Base_co * k = p->next;
                //on lib�re la premi�re r�gle
                free(p);
                return k;// on retourne le pointeur qu'on avait cr�e
            }
        }

    // si la cha�ne de caract�re ne correspond pas � la premi�re r�gle
    // on effectue une boucle while qui va comparer la chaine de carcat�re saisit et le nom de la recettte pour chaque r�gle
    while ( p != NULL )
    {
        Base_co * tmp = p ;//on cr�e un pointeur qu'on affectera le pointeur p
        p= p->next;// on affecte � p  , l'�lement suivant de p
        if (strcmp(p->nom,c)== 0 )//on compare la cha�ne de caract�re saisit , et le nom de la recette de la r�gle du pointeur p
        {
            //si les deux cha�nes de caract�res correspondent
            if (p->next == NULL )// on v�iifie s'il existe un r�gle apr�s celle du pointeur p
            {
                //si oui , alors on fait pointer l'element suiviant de tmp   vers NULL
                tmp->next = NULL;
                //puis on libere le pointeur p
                free(p);
                return ancienneBaseCo;//on retourne la  liste  base_co modifi�
            }
            else
            {
                //si non , alors on fait pointer l'element suivant de tmp vers l'element suivant de p, afin de lib�rer p sans causer de probl�me � la liste
                tmp->next = p->next;
                //on lib�re ainsi p
                free(p);
                return ancienneBaseCo;
            }
        }

    }
    }
    printf(" \n Le nom de cette recette  ne correspond � aucune des pizzas \n  ");
    return ancienneBaseCo;
}


char * Queue_list(Liste_regle l)        /*permet de recup�rer la dernier valeur d'un liste (notamment pour recup�rer la conclusion d'un r�gle)*/
{
    while (l->next !=NULL)
    {
        l=l->next;
    }
    return l->prop;
}
