#ifndef _COADAH_
#define _COADAH_
#include "displayer.h"
#define true (1)
#define false (0)

typedef unsigned char boolean;

/*definire tip referinþã la un nod al cozii*/
typedef struct tip_nod * tip_referinta_nod;

/*definire tip nod al cozii*/
typedef struct tip_nod {
  ref element;
  tip_referinta_nod urm;
}
tip_nod;

/* Definirea structurii de date tip_coada*/
typedef struct tip_coada {
  tip_referinta_nod inceput, spate;
}
tip_coada;

void initializeaza(tip_coada * c);
/*creaza coada vida c*/
boolean vid(tip_coada c);
/*returneazã true dacã coada este vidã, false altfel*/
ref cap(tip_coada c);
/*returneazã elementul din capul cozii, sau null dacã coada este vidã*/
void adauga(ref x, tip_coada * c);
/*adaugã un element la spatele cozii*/
void scoate(tip_coada * c);
/*suprimã primul element al cozii daca existã*/

#endif // coada
