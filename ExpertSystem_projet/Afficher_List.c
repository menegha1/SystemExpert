#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "afficher_List.h"

void afficherListe_regle(Liste_regle  l)    /*Afficher une liste de regle (avec des prémisses et une conclusion à la fin*/
{
    if (l == NULL)
    {
        printf("===EMPTY LIST===");
    }
    else
    {
        Regle * p = l;
        printf("Les ingredients sont : ");
        while (p->next != NULL)
        {
            printf("  -> %s", p->prop); /*affichage des prémisses*/
            p = p->next;
        }
        printf("\nEt le nom de la pizza est ~ %s \n", p->prop); /*la conclusion de cette liste*/
    }
}
/*Affichage de tout la liste type Liste_bace cette-à-dire une liste de regle avec dedans la liste de prémisse et conclusion*/
void afficherListe_baseco(Liste_baseco  x)
{
    int i= 1;
    if (x == NULL)
    {
        printf("===EMPTY LIST===");
    }
    else
    {
        Liste_baseco  p = x;

        while (p != NULL)
        {
            printf(" nom de la recette : %s | Liste numero %d: \n\n ",p->nom, i); /*Nom de la liste baseco suivie de sa liste de prémisse et conclusion*/
            afficherListe_regle(p->l2);
            p = p->next;
            i++;
        }
    }
}

void afficherListe_conclusion(Liste_regle  l)   /*Fonction permettant d'afficher la liste des conclusions après la recherche par le moteur d'inférence des conclusions possible*/
{
    if (l == NULL)
    {
        printf("===EMPTY LIST===");
    }
    else
    {
        Regle * p = l;
        printf("Les pizzas que vous souhaitez sont : ");
        while (p != NULL)
        {
            printf("  -> %s \n", p->prop);
            p = p->next;
        }
    }
}
