


int main(int argc, char * argv[]) {
    ARBRE arbre;
    arbre = creer_arbre(2,creer_arbre(2,NULL,NULL),creer_arbre(3,NULL,NULL));
    return 0;
}

ARBRE creer_arbre(int x,ARBRE arbreg,ARBRE arbred) {
  ARBRE a = (ARBRE)malloc(sizeof(noeud));
  if(a != NULL) {
    a->ag = arbreg;
    a->ad = arbred;
    a->val = x;
  }
  return a;
}