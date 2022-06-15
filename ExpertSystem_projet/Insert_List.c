#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "insert_List.h"

Liste_regle insert_proposition(Liste_regle l, char *p)/*Permet d'ajouter dans une liste de prémisse et conclusion des caractères (utile pour créer et initialiser les règles*/
{
    Liste_regle newel;
    newel = malloc(sizeof(Regle));
    newel->prop = p;
    newel->next= NULL;

    if(l == NULL)
    {
        return newel;
    }
    else
    {
        Liste_regle q =  l;     /*l'ajout du caractère se fait en Queue de liste*/
        while(q->next != NULL)
        {
            q = q->next;
        }
        q->next= newel;
        return l;
    }
}

Liste_baseco ajouter_regle(Liste_baseco anciennelist)/*permet de créer tout la nouvelle regle avec son nom, sa réponse attendu et sa liste de prémisse et conclusion*/
{

    int k=0;
    int ok=0;
    int retour;
    char **ptr;// on crée une chaîne de caractère avec deux pointeurs

    char *nom = (char*) malloc(50 * sizeof(char));//on crée une autre chaîne de caractère , qu'on allouera avec l'espace suffisant

    Liste_regle l = NULL; // on crée une nouvelle liste de premisse

    //on effectue maintenant une contrôle de saisie avec une boucle , où on en sortira quand l'utilisateur aura saisit la bonne variable
    while(!ok)
    {
        system("cls");
        setbuf(stdout, NULL);
        printf("Indiquer le nombre d'ingredient qu'il vous faut \n");
        setbuf(stdout, NULL);
        retour = scanf("%d%*[^\n]", &k);//on affecte à la constante " retour " le test retour du scanf que l'utilisateur aura saisie
        if(!retour)
        {
            //s'il ne vaut pas 1 , alors la saisie a échoué
            // alors  on vide le flux entrant avec un getchar
            int c;
            while ( ((c = getchar()) != '\n') && c != EOF);

            //on refera ainsi la boucle
            printf("errreur d'entree, vous n'avez pas rentree un nombre \n");
            printf("Veuillez recommence s'il vous plait . \n");
            system("pause");
        }
        else
        {
            //S'il vaut 1 , alors la saisie à réussi
            getchar();//on enlève le \n à a fin de la chaîne de caractère saisie avec un getchzr
            ok = 1; //on affecte 1 à la constance " ok " , afin de ne pas recommencer la boucle
        }
    }

    ptr =  (char *) malloc(k * sizeof(char)); // on alloue au premier pointeur de "ptr" la mémoire suffisant soir
    // le nombre d'ingredient que  l'utilisateur aura saisie

    // on effectue une boucle for  en fonctino du nombre d'ingrédients
    for (int i=0; i<k; i++)
    {
        ptr[i] = (char *) malloc(50 * sizeof(char));//on alloue pour une chaîne de caractère(correspondant à un ingréident)  la mémoire suffisante
        printf("L'ingrédiant est (un par un) :  ");
        scanf("%s", ptr[i]);
        l = insert_proposition(l,ptr[i]);//on insère la propostion que l'utilisateur aura marqué dans la liste de premisse précdement crée
    }
    printf(" indiquez le nom de cette pizza :  ");
    ptr[k] = (char *) malloc(50 * sizeof(char));//on alloue la mémoire suffisante pour la chaîne de caractère corresponsant à la conclusion
    scanf("%s", ptr[k]);//on récupère la chaîne de caractère saisit par l'utilisateur( correspondant à la conclusion)

    // on l'insère à la liste de premisse " l " , en ajoutant un " \n"
    // afin de faciliter la lecture et écriture  des fichiers
    l = insert_proposition(l,strcat(ptr[k],"\n"));
    printf(" \n Quel est le nom de cette recette ?(ex: pizza-italienne, pizza-du-restaurant...) :  ");
    scanf("%s", nom);//on récupère la chaîne de caractère saisit par l'utilisateur( correspondant au nom de a recette )

    Base_co* newel;//on crée un nouvel element ayant la structure Base_co
    newel = (Base_co*) malloc(sizeof(Base_co));//on alloue la mémore nécessaire

    // on lui affecte les différentes variables nécessaires pour crée une nouvelle règle
    newel->l2 = l;// on lui affecte la liste de premisse
    newel->nom = nom;// le nom de la recette
    newel ->repattendu = count_normal(l);// le nombre de propositions ( conclusion exclus )
    newel->next= NULL;

    // on fait en sorte d'insérer cette nouvelle règle  à la fin de la liste Base_co ( liste de règle)
    if(anciennelist != NULL)
    {
        Liste_baseco p = anciennelist;
        while(p->next != NULL)
        {
            p = p->next;
        }
        p->next= newel;

        return anciennelist;
    }
}

Liste_baseco insert_regle_predefini(Liste_baseco listbase,Liste_regle l_regle,char * nom_regle) /*Permet de recupérer les informations sur une règle lors de sa création (lorsqu'on ajoute une règle)*/
{


    Base_co* newel;
    newel = (Base_co*) malloc(sizeof(Base_co));
    newel->l2 = l_regle;    /*ajout de la liste de premisse et conclusion*/
    newel->repattendu = count_normal(l_regle);  /*entier important pour le moteur d'inférence*/
    newel->nom = nom_regle; /*nom de la règle*/
    newel->next= NULL;
    if(listbase == NULL)
    {
        return newel;
    }
    else
    {
        Liste_baseco p = listbase;  /*ajout des nouvelle règle en queue de liste*/
        while(p->next != NULL)
        {
            p = p->next;
        }
        p->next= newel;
        return listbase;
    }
}
