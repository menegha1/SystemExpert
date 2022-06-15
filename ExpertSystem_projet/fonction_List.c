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

int search_Val(Liste_regle list,char * e)   /*Cherche si une valeur est déjà présente dans une liste (le programme ne parcours pas la dernière valeur (qui est la conclusion) et c'est une fonction RECURSIVE*/
{

    if( list ->next == NULL)  /*==> Différence avec search_Valconclu()*/
    {
        return 1;   /*1 == Non il n'y a pas de valeur similaire dans la liste*/
    }
    if( list == NULL)
    {
        return 1 ;
    }
    else
    {
        if (strcmp(list->prop,e)==0)    /* Le caractère prop(list) est similaire au caractère e*/
        {
            return 0; /*0 == Oui il y a une valeur similaire dans la liste*/
        }
    }
    return search_Val(list->next,e);
}
int search_Valconclu(Liste_regle list,char * e)     /*Même fonction que search_val() mais la comparaison se fait dans tout la liste (même le dernier caractère de la liste) et la fonction est RECURSIVE*/
{
    int cont=1;
    if( list == NULL)   /*==> Différence avec search_val()*/
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

    char * c ;//on crée une chaîne de caractèr en pointeur
    c = (char*) malloc(100 * sizeof(char));//on alloue la mémore suffisantes pour la chaîne de caractère
    Base_co * p = ancienneBaseCo ; // on crée un pointeur de la base_co actuelle

    printf(" \nQuel est le nom de la recette (exemple : pizza-italienne) a supprimer :  ");
    scanf("%s",c);//on lit une  chaîne de caractère, soit le nom de la recette qu'on souhaite supprimer

    if (ancienneBaseCo == NULL)// on verifi si la base_co n'est pas vide
    {
        printf(" La liste de règle est vide \n \n");
        return NULL;// si oui , alors on finit  la fonction
    }
    else
    {
        if (strcmp(p->nom,c)== 0 )// on vérifie si la chaîne de caractère saisit correspond  au nom de la recette de la première regle
        {
            //si oui,  on vérifie alors si il existe une prochaine règle
            if (p->next == NULL )
            {
                //si  la liste comprend qu'une seul règle alors on libère la liste actuelle
                free(p);
                return ancienneBaseCo;
            }
            else
            {
                //si il existe d'autres règles , alors on crée un pointeur qui va pointer sur la prochaine règle la liste actuelle
                Base_co * k = p->next;
                //on libère la première règle
                free(p);
                return k;// on retourne le pointeur qu'on avait crée
            }
        }

    // si la chaîne de caractère ne correspond pas à la première règle
    // on effectue une boucle while qui va comparer la chaine de carcatère saisit et le nom de la recettte pour chaque règle
    while ( p != NULL )
    {
        Base_co * tmp = p ;//on crée un pointeur qu'on affectera le pointeur p
        p= p->next;// on affecte à p  , l'élement suivant de p
        if (strcmp(p->nom,c)== 0 )//on compare la chaîne de caractère saisit , et le nom de la recette de la règle du pointeur p
        {
            //si les deux chaînes de caractères correspondent
            if (p->next == NULL )// on véiifie s'il existe un règle après celle du pointeur p
            {
                //si oui , alors on fait pointer l'element suiviant de tmp   vers NULL
                tmp->next = NULL;
                //puis on libere le pointeur p
                free(p);
                return ancienneBaseCo;//on retourne la  liste  base_co modifié
            }
            else
            {
                //si non , alors on fait pointer l'element suivant de tmp vers l'element suivant de p, afin de libérer p sans causer de problème à la liste
                tmp->next = p->next;
                //on libère ainsi p
                free(p);
                return ancienneBaseCo;
            }
        }

    }
    }
    printf(" \n Le nom de cette recette  ne correspond à aucune des pizzas \n  ");
    return ancienneBaseCo;
}


char * Queue_list(Liste_regle l)        /*permet de recupérer la dernier valeur d'un liste (notamment pour recupérer la conclusion d'un règle)*/
{
    while (l->next !=NULL)
    {
        l=l->next;
    }
    return l->prop;
}
