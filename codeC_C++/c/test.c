#include <stdio.h>
#include <stdlib.h>

typedef struct noeud{
    int x;
    struct noeud * ag;
    struct noeud * ad;
}noeud;
struct noeud *mon_point;


int main(int argc, char * argv)
{
    /*
    int tableau[10]; 
    volatile int a=0;

    noeud *ag = NULL;
    ag = (noeud *)malloc(sizeof(noeud));
    ag->x = 10;
    
    printf("%d",ag->x);
    */
    int tableau[10] = {0}; 
    tableau[4],tableau[5],tableau[6] = 12,12,12; 
    

    return 0;
}
