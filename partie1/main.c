#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct partition{
    int adr;
    int taille;
    int etat;
}partition;
//etat 1 occupe ,0 libre
typedef struct node {
  struct partition data;
  struct node *svt;
}node;

typedef struct processus{
   int id; //identite
   float ia;  //instant arrive
   float te; //temps execution
}processus;

typedef struct nodeF{
   struct processus data;
   struct nodeF *svt;
}nodeF;
//liste de partitions
typedef  node* liste;

liste Listepar(){
    srand(time(NULL));
    int i;
    liste L = NULL ;   //initialiser la tete a nill
    liste p,q;
    //creation du premier element
    L=(node*)malloc(sizeof(node));

    //remplicage de premier element
    L->data.adr = rand() % 100 +1;
    do{L->data.taille = (rand()%200)*10; }while(L->data.taille == 0); //si taille=0 on cherche une nouv valeur
    L->data.etat= rand()%2 ;
    p = L;//p pointe sur la tete
    q = L;//q pointe sur la tete

    for(i=0;i<15;i++){ //boucle de creation des elements
             p=(node *)malloc(sizeof(node));
             p->data.adr= q->data.adr + q->data.taille;
              do{p->data.taille = ( rand()%200 )*10 ; }while(p->data.taille == 0);
             p->data.etat= rand()%2;
             q->svt = p; //chainage d'element
             q=p;
    }
    p->svt = NULL; //dernier element n'a pas un svt
    return(L);
}
 void affichageListepar(liste L){
    liste p;
    p = L;
    while(p != NULL){
            printf(" %d %d %d \n", p->data.adr, p->data.taille , p->data.etat);
            p = p->svt;
    }
}



typedef struct file{
  nodeF* tete;
  nodeF* queue;
}file;

//Procedure InitFile(E/S/ F:File);
void initfile(file *f){
  f->tete=NULL;
  f->queue=NULL;
 
}

void enfiler(file *f , processus x ){
    nodeF* newf=(nodeF*)malloc(sizeof(nodeF));
    newf->data.id = x.id;
    newf->data.ia=x.ia;
    newf->data.te= x.te;
   newf->svt=NULL;
   if ( f->queue == NULL) {f->tete=newf; f->queue=newf;}//file vide
   else{ (f->queue)->svt=newf; f->queue=newf; };
}

processus defiler(file *f ){
    nodeF* temp;
    processus x;
    temp = (f->tete);
    x.ia=((f->tete)->data).ia;
    x.id=((f->tete)->data).id;
    x.te=((f->tete)->data).te;
    f->tete=(f->tete)->svt;
    if(f->tete==NULL){ f->queue=NULL;  }
    free(temp);
    return x;
}


 processus TeteFile(file *f){
  return ((f->tete)->data);
 }


int FileVide(file *f){
      if(f->tete==NULL) {return 1;}  else{ return 0;}
}
//affiche et affecte le tout dans r puis f=r
void Affichefile(file f){
    processus x;
    file r;
    printf("affichage begins\n");
    initfile(&r);
    while (FileVide(&f)!=1){
        x=defiler(&f);
        printf("id= %d  ia=%0.2f te=%0.2f \n", x.id , x.ia , x.te );

        enfiler(&r , x );
    }
    f=r;
}

file createfile(){
  srand(time(NULL));
  float r_ia=0;
  float r_te;
  file F;
  processus p;
  int n=rand() % 15;
  printf("n= %d \n", n);
  initfile(&F);
  for (int i=0; i<n ; i++ ){
    p.id=i; 
    r_ia=r_ia+( rand() % 12 + 0);
    p.ia=r_ia ; 
    r_te= rand() % 60 + 5;
    p.te=r_te;
    enfiler(&F, p);
      }

//hello
return (F);
}


int main(){
  //partie file
   file f;
   f=createfile();
   Affichefile(f);
//partie liste
liste L;
    L= Listepar();
    printf("l'affichage de la liste : \n");
    affichageListepar(L);

    return 0;
}
