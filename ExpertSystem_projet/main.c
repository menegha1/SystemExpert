#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afficher_List.h"
#include "fonction_List.h"
#include "insert_List.h"
#include "moteur_inference.h"
#include "sauvegarder_regle.h"

int main()                  /*�Pr�miere fonction d�marrant le programme et permet de controler toutes les fonctionnaliter du programme*/
{
    int rep_main;   /*entier pour donn�e une reponse sur quelle fonctionnaliter faire*/
    char w ;     /*Caract�re pour savoir si l'utilisateur continue ou non d'ajouter des r�gle*/
    int nb;     /*entier caract�risant le nombre d'ingr�dient dans la base de fait*/
    int ok=0;   /*entiers pour la verification de la saisie*/
    int retour;

    /*Ecran d'accueil avec choix d'actions*/

    while(!ok)
    {
        system("cls");
        printf("++++++++++++++++++++++++++++++++++++++++++++++++++\n+                                                +\n+                                                +\n+       Bienvenue sur notre systeme expert       +\n+                Theme : Les pizza               +\n+                                                +\n++++++++++++++++++++++++++++++++++++++++++++++++++");
        printf("\n\n======QUE SOUHAITEZ VOUS FAIRE ?======\n");
        printf("\n1->Afficher les pizzas deja presente sur le programme\n2->Ajouter une pizza au programme\n3->Supprimer une pizza du programme\n4->Chercher une pizza � partir des ingr�dients\n5->Quitter le programme\n\n");
        retour = scanf("%d%*[^\n]", &rep_main);

        /*verification de la saisie*/

        if (!retour)
        {
            int c;
            while (((c = getchar()) != '\n') && c != EOF)
                ;;
            printf("on vous a demande de saisir un nombre\n");
            printf("veuillez recommencer :\n");
            system("pause");

        }
        else
        {
            if(rep_main!=1 && rep_main !=2 && rep_main !=3 && rep_main !=4 && rep_main !=5)
            {
                printf("Votre nombre ne correspond aux nombres affiches \n");
                printf("veuillez recommencer :\n");
                system("pause");
            }
            else
            {
                getchar();
                ok = 1;
                system("cls");
            }
        }

    }
    /*chargement des r�gles contenu dans un fichier "test.txt"*/

    Liste_baseco ListBaseCo = NULL;
    ListBaseCo = load_liste(ListBaseCo);

    /*switch pour manipuler les fonctions necessaire pour effectuer une action*/

    switch(rep_main)
    {
    case 1:     /*Afficher la liste des r�gles*/
        afficherListe_baseco(ListBaseCo);
        system("pause");
        system("cls");
        free(ListBaseCo);
        main();         /*permet de revenir � l'�cran d'accueil*/
        break;
    case 2:     /*Ajouter une r�gle*/
        w='o';
        while (w == 'o')
        {
            printf("Les listes de pizza deja pr�sente sont ci-dessous : \n\n\n");
            afficherListe_baseco(ListBaseCo);
            printf("\nVotre nouvelle recette :\n\n");
            ListBaseCo = ajouter_regle(ListBaseCo);   /*fonction pour cr�er et ajouter la nouvelle r�gle*/
            save_liste(ListBaseCo);     /*Fonction pour sauvegarder la nouvelle liste modifier dans le fichier*/
            printf("\n\nVoulez-vous rajouter des regles  ? (o/n)");
            scanf("%s",&w);
            while(w != 'o' || w != 'n')     /*verification de saisie*/
            {
                printf("erreur d'entr�e \n Veuillez recommencez s'il vous pla�t : \n ");
                printf("\nVoulez-vous rajouter des regles  ? (o/n)");
                scanf("%s",&w);
            }
        }
        printf("\nFelicitation la nouvelle recette � �t� enregister !\n\n");
        free(ListBaseCo);
        system("pause");
        system("cls");
        main();
        break;
    case 3 :        /*Supprimer une liste*/
        printf("Les listes de pizza deja pr�sente sont ci-dessous : \n\n\n");
        afficherListe_baseco(ListBaseCo);
        ListBaseCo=supprimerListe(ListBaseCo);      /*fonction demandant le nom de la liste � supprimer et l'a supprime*/
        printf("votre recette � �t� supprime");
        save_liste(ListBaseCo);
        free(ListBaseCo);
        system("pause");
        system("cls");
        main();
        break;
    case 4 :        /*Rechercher une conclusion � partir d'un base de fait*/
        ok=0;
        while(!ok)  /*verrification de la saisie*/
        {
            system("cls");

            printf("Combien d'ingrediants souhaitez vous dans votre pizza?  \n");
            retour = scanf("%d%*[^\n]", &nb);
            if(!retour)
            {
                int c;
                while ( ((c = getchar()) != '\n') && c != EOF);
                printf("errreur d'entree, vous n'avez pas rentree un nombre \n");
                printf("Veuillez recommence s'il vous plait . \n");
                system("pause");
            }
            else
            {
                getchar();
                ok = 1;
            }
        }
        Liste_regle conclu = NULL;  /*Liste contenant les futurs proposition de l'utilisateur � tester dans les r�gles*/
        Liste_regle base_fait =NULL;    /*Liste contenant toutes les conclusions � la fin de cette action*/
        afficherListe_baseco(ListBaseCo);
        for (int i=0; i<nb; i++)        /*Recup�ration de la liste de la base de fait*/
        {
            char * ingredient;
            ingredient = (char*)malloc(50*sizeof(char));
            printf("quel sont les ingredients (un par un) ?\n");
            scanf("%s",ingredient);
            base_fait = insert_proposition(base_fait,ingredient);
        }
        afficherListe_regle(base_fait);
        printf("\n\n\n");
        conclu = Jouer(ListBaseCo,base_fait,nb,conclu); /*fonction repr�sentant le moteur d'inf�rence*/
        afficherListe_conclusion(conclu);   /*affichage des conclusions*/
        free(ListBaseCo);
        free(conclu);
        free(base_fait);
        system("pause");
        system("cls");
        main();
        break;
    }
    /*Pour quitter le programme*/
    printf("======MERCI D'AVOIR JOUER======\n\n***nous avons pris en compte vos modification***\n\n++++++++++A BIENTOT++++++++++\n\n");
    return EXIT_SUCCESS;
}
