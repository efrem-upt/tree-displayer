#ifndef _DISPLAYERH_
#define _DISPLAYERH_

#define n (31) /* numar chei */
#define lch (10) /* lungime maxima cuvant cheie */
#define index (n + 1) /* dimensiune tablouri de chei */
#define pozLin ll
#define ll (130) /* lățime linie de afișat */
#define ffl (100) /* lungime path fisier intrare */

typedef char alfa[lch]; /* tip de date string[lch] */

typedef struct ref {
  alfa cheie;
  int poz; /* pozitia pe rand a cheii */
  struct ref * sting, * drept;
}
nod;

typedef nod * ref;

char ch;
int k1, k2;
alfa id = {}; /* identificator sau cheie */
alfa chei[index]; /* tablou de indentificatori / chei */
int i, j, k;
int a[index]; /*tablou frecvente chei*/
int b[index]; /*tablou frecvente interchei*/
int p[index][index]; /*matrice lungimi drumuri ponderate*/
int w[index][index]; /*matrice ponderi arbori optimi*/
int r[index][index]; /*matrice radacini arbori optimi*/
int suma; /* suma frecvente chei */
int sumb; /* suma frecvente interchei */
char litere[53]; /* literele alfabetului englez mari si mici */
char cifre[11]; /* cifrele de la 0..9 */

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
void eliberare(ref rad);
/* elimina memoria alocata stocarii dinamice a arborelui */

#endif // displayer
