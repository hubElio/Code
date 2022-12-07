#include <stdio.h>//printf
#include <stdlib.h>//malloc
#include "Structure_de_donnee.h" 



ARBRE creer_arbre(int _val,ARBRE _ag,ARBRE _ad) {
    ARBRE tempArbre = (noeud *) malloc(sizeof(noeud));
    tempArbre->val = _val;
    tempArbre->ag = _ag;
    tempArbre->ad = _ad;
    return tempArbre;
}

void afficher_arbre_v1(ARBRE a) {
    printf("(");
    if(a != NULL) {
        printf("%d",a->val);
        if(a->ag != NULL) {
            printf(",");
            afficher_arbre_v1(a->ag);
        }else {
            printf(",");
            printf("*");
        } 
        if (a->ad != NULL) {
            printf(",");
            afficher_arbre_v1(a->ad);
        } else {
            printf(",");
            printf("*");
        }
    } else {
        printf("*");
    }
    printf(")");
}

int main(int argc, char * argv[]){
    printf("\n");
    afficher_arbre_v1(creer_arbre(13,creer_arbre(15,creer_arbre(1,NULL,NULL),NULL),creer_arbre(9,NULL,NULL)));
    printf("\n");
    int bool = 0;
    rehcerche_arbre(1,creer_arbre(13,creer_arbre(15,creer_arbre(1,NULL,NULL),NULL),creer_arbre(9,NULL,NULL)),&bool)
    printf("%d",bool);
    return 0;
}

void rehcerche_arbre(int ent,ARBRE a,int * bool) {
    int tempBool = 0;
    if (a != NULL) {
        if(a->val == ent) {
            tempBool = 1;
        }
        else if(a->ag != NULL) {rehcerche_arbre(ent,a->ag,bool);}
        else if(a->ad != NULL) {rehcerche_arbre(ent,a->ad, bool);}
    } else {tempBool =0;}
    *bool = tempBool;
}