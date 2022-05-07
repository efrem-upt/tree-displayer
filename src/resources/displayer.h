#ifndef _DISPLAYERH_
#define _DISPLAYERH_

#define n 32
#define lch 10
#define index n + 1
#define pozLin ll
#define ll 150 /* lățime linie de afișat */

typedef char alfa[lch];

char ch;
int k1, k2; // identificator sau cheie
alfa id = {}; /* identificator sau cheie */
alfa chei[n + 1];
int i, j, k;
int a[n + 1];
int b[index];
int p[index][index], w[index][index];
int r[index][index];
int r[index][index];
int suma, sumb;
char litere[53];
char cifre[11];

typedef struct ref {
  alfa cheie;
  int poz;
  struct ref * sting, * drept, * leg;
}
nod;

typedef nod * ref;

int DrumArbEch(int i, int j);
/* Generează în manieră recursivă matricea r corespunzătoare
  arborelui perfect echilibrat care poate fi construit
  utilizând cele n chei date şi returnează lungimea drumului
  acestui arbore */
void ArbOpt();
/* Construieşte arborele binar optim pornind de la matricea w a
  ponderilor nodurilor. De fapt se generează matricea r cu
  indicii cheilor care reprezintă rădăcinile subarborilor
  optimi şi matricea p cu lungimile corespunzătoare ale
  drumurilor asociate */
ref Arbore(int i, int j, int * k);
/* Generează structura de date corespunzătoare arborelui
  optim. Porneşte de la matricea r care conţine rădăcinile
  subarborilor binari optimi si returnează referinţa la
  rădăcina arborelui optim construit */
void AfiseazaArbore();
/* Realizează afişarea efectivă a structurii arborelui şi are
  drept parametri de intrare indicii i şi j care delimitează
  arborele de afişat */

#endif // displayer
