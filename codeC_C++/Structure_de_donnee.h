typedef struct noeud {
    int val;
    struct noeud * ag;
    struct noeud * ad;
} noeud;

typedef noeud * ARBRE;


void rehcerche_arbre(int,ARBRE,int);
void afficher_arbre_v1(ARBRE);
ARBRE creer_arbre(int,ARBRE,ARBRE);