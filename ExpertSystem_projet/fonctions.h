#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED

/*Liste pour des pr�misses et conclusion ET utiliser pour des listes de caract�re pour la base de fait et liste de conclusion*/

typedef struct regle
{

    char *prop;// exemple  fromage
    struct regle* next;
} Regle;
typedef Regle* Liste_regle;

/*Liste des r�gles contenant un nom, le nombre de reponse attendu pour le moteur d'inf�rence et une liste de pr�misse et conclusion*/

typedef struct base_co
{
    char *nom;
    int repattendu;
    Liste_regle l2;
    struct base_co* next;
} Base_co;
typedef Base_co* Liste_baseco;

/*Les Fonctions utiliser dans le programme*/


//Insert_List.c

//Moteur_inf�rence.c

#endif // FONCTIONS_H_INCLUDED
