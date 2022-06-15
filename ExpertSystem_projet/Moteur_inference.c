#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moteur_inference.h"
/*Cette fonction va vérifier si la conclusion est nouvelle dans la liste de la conclusion. Si oui, alors le moteur doit parcourir une nouvelle
fois la liste de règle et on ajoute cette conclusion dans la liste des conclusions. Si non, alors, on ne fait pas attention à cette conclusion
et on continu à parcourir la liste de regle*/
Liste_regle recherche_result(Liste_baseco ListBaseCo,int reponse,Liste_regle list_regle,Liste_regle conclu,Liste_regle Base_fait,int nb, int * k)
{
    char * simple_conclu;   /*conclusion trouver dans la liste de premisse et conclusion*/
    char * adr_retour_ligne;    /*caractère pour retirer "\n" du caractère enregister dans la liste (probleme lié avec la sauvegarde dans le fichier*/
    simple_conclu=(char *)malloc(50*sizeof(char));
    if (ListBaseCo->repattendu==reponse)    /*verrification si la liste de premisse est bonne par rapport à la base de fait*/
    {
        simple_conclu = Queue_list(list_regle);     /*recupération de la conclusion*/
        adr_retour_ligne = strpbrk(simple_conclu,"\n"); /*Suppression de "\n" de cette conclusion*/
        if(adr_retour_ligne != NULL)
        {
            *adr_retour_ligne = 0;
        }
        if (search_Valconclu(conclu,simple_conclu)==0)  /*recherche si la conclusion appartient déjà à la conclusion*/
        {
            return conclu;
        }
        else    /*Si non on enregistre la conclusion dans la liste de conclusion*/
        {
            *k = 1 ;
            Base_fait = insert_proposition(Base_fait,simple_conclu);
            conclu = insert_proposition(conclu,simple_conclu);
            return conclu;
        }

    }
    return conclu;
}
/*La fonction Jouer() représente le moteur d'inférence : celui-ci va recupérer une liste de premisse et conclusion d'une règle puis avec la
comparer avec la base de fait demander à l'utilisatateur. A chaque fois que le caracère de la base de fait est contenu de la liste de prémisse
on ajoute +1 à l'entier reponse. Puis on compare cette entier avec le nombre de prémisse présente dans cette règle et si elle est similaire
on recupère la conclusion*/
Liste_regle Jouer(Liste_baseco ListBaseCo,Liste_regle  base_fait,int nb,Liste_regle  conclu)
{
    int reponse=0;  /*entier content le nombre de réponse similaire entre base de fait et la liste de prémisse*/
    Liste_baseco  p = ListBaseCo;
    while (p !=NULL)        /*parcours de tout les règles*/
    {
        int k = 0 ;
        Liste_regle temp = NULL;
        temp=p->l2;         /*récupération de la liste de prémisse et conclusion de la règle*/
        Liste_regle  q = base_fait;
        while(q != NULL)    /*parcours de tout la base de fait*/
        {
            if (search_Val(temp, q->prop)==0)   /*recherche si la liste de prémisse possède le caractère de la base de fait*/
            {
                reponse=reponse+1;

            }
            q = q->next;

        }
        conclu = recherche_result(p,reponse,temp,conclu,base_fait,nb,&k);  /*fonction controlant la récupération de la conclusion*/
        reponse = 0 ;
        if (k == 1 )    /*Permet de recommencer à chercher depuis le début de la liste des règles SINON on passe à une autre règle*/
        {
            p = ListBaseCo ;
        }
        else
        {
            p=p->next;
        }

    }
    return conclu;
}
