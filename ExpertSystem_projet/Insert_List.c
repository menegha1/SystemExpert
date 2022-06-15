#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "insert_List.h"

Liste_regle insert_proposition(Liste_regle l, char *p)/*Permet d'ajouter dans une liste de pr�misse et conclusion des caract�res (utile pour cr�er et initialiser les r�gles*/
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
        Liste_regle q =  l;     /*l'ajout du caract�re se fait en Queue de liste*/
        while(q->next != NULL)
        {
            q = q->next;
        }
        q->next= newel;
        return l;
    }
}

Liste_baseco ajouter_regle(Liste_baseco anciennelist)/*permet de cr�er tout la nouvelle regle avec son nom, sa r�ponse attendu et sa liste de pr�misse et conclusion*/
{

    int k=0;
    int ok=0;
    int retour;
    char **ptr;// on cr�e une cha�ne de caract�re avec deux pointeurs

    char *nom = (char*) malloc(50 * sizeof(char));//on cr�e une autre cha�ne de caract�re , qu'on allouera avec l'espace suffisant

    Liste_regle l = NULL; // on cr�e une nouvelle liste de premisse

    //on effectue maintenant une contr�le de saisie avec une boucle , o� on en sortira quand l'utilisateur aura saisit la bonne variable
    while(!ok)
    {
        system("cls");
        setbuf(stdout, NULL);
        printf("Indiquer le nombre d'ingredient qu'il vous faut \n");
        setbuf(stdout, NULL);
        retour = scanf("%d%*[^\n]", &k);//on affecte � la constante " retour " le test retour du scanf que l'utilisateur aura saisie
        if(!retour)
        {
            //s'il ne vaut pas 1 , alors la saisie a �chou�
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
            //S'il vaut 1 , alors la saisie � r�ussi
            getchar();//on enl�ve le \n � a fin de la cha�ne de caract�re saisie avec un getchzr
            ok = 1; //on affecte 1 � la constance " ok " , afin de ne pas recommencer la boucle
        }
    }

    ptr =  (char *) malloc(k * sizeof(char)); // on alloue au premier pointeur de "ptr" la m�moire suffisant soir
    // le nombre d'ingredient que  l'utilisateur aura saisie

    // on effectue une boucle for  en fonctino du nombre d'ingr�dients
    for (int i=0; i<k; i++)
    {
        ptr[i] = (char *) malloc(50 * sizeof(char));//on alloue pour une cha�ne de caract�re(correspondant � un ingr�ident)  la m�moire suffisante
        printf("L'ingr�diant est (un par un) :  ");
        scanf("%s", ptr[i]);
        l = insert_proposition(l,ptr[i]);//on ins�re la propostion que l'utilisateur aura marqu� dans la liste de premisse pr�cdement cr�e
    }
    printf(" indiquez le nom de cette pizza :  ");
    ptr[k] = (char *) malloc(50 * sizeof(char));//on alloue la m�moire suffisante pour la cha�ne de caract�re corresponsant � la conclusion
    scanf("%s", ptr[k]);//on r�cup�re la cha�ne de caract�re saisit par l'utilisateur( correspondant � la conclusion)

    // on l'ins�re � la liste de premisse " l " , en ajoutant un " \n"
    // afin de faciliter la lecture et �criture  des fichiers
    l = insert_proposition(l,strcat(ptr[k],"\n"));
    printf(" \n Quel est le nom de cette recette ?(ex: pizza-italienne, pizza-du-restaurant...) :  ");
    scanf("%s", nom);//on r�cup�re la cha�ne de caract�re saisit par l'utilisateur( correspondant au nom de a recette )

    Base_co* newel;//on cr�e un nouvel element ayant la structure Base_co
    newel = (Base_co*) malloc(sizeof(Base_co));//on alloue la m�more n�cessaire

    // on lui affecte les diff�rentes variables n�cessaires pour cr�e une nouvelle r�gle
    newel->l2 = l;// on lui affecte la liste de premisse
    newel->nom = nom;// le nom de la recette
    newel ->repattendu = count_normal(l);// le nombre de propositions ( conclusion exclus )
    newel->next= NULL;

    // on fait en sorte d'ins�rer cette nouvelle r�gle  � la fin de la liste Base_co ( liste de r�gle)
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

Liste_baseco insert_regle_predefini(Liste_baseco listbase,Liste_regle l_regle,char * nom_regle) /*Permet de recup�rer les informations sur une r�gle lors de sa cr�ation (lorsqu'on ajoute une r�gle)*/
{


    Base_co* newel;
    newel = (Base_co*) malloc(sizeof(Base_co));
    newel->l2 = l_regle;    /*ajout de la liste de premisse et conclusion*/
    newel->repattendu = count_normal(l_regle);  /*entier important pour le moteur d'inf�rence*/
    newel->nom = nom_regle; /*nom de la r�gle*/
    newel->next= NULL;
    if(listbase == NULL)
    {
        return newel;
    }
    else
    {
        Liste_baseco p = listbase;  /*ajout des nouvelle r�gle en queue de liste*/
        while(p->next != NULL)
        {
            p = p->next;
        }
        p->next= newel;
        return listbase;
    }
}
