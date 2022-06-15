#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

/*Liste pour des prémisses et conclusion ET utiliser pour des listes de caractère pour la base de fait et liste de conclusion*/

typedef struct regle
{

    char *prop;// exemple  fromage
    struct regle* next;
} Regle;
typedef Regle* Liste_regle;

/*Liste des règles contenant un nom, le nombre de reponse attendu pour le moteur d'inférence et une liste de prémisse et conclusion*/

typedef struct base_co
{
    char *nom;
    int repattendu;
    Liste_regle l2;
    struct base_co* next;
} Base_co;
typedef Base_co* Liste_baseco;

#endif // STRUCTURE_H_INCLUDED
