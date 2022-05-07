#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define n 31
#define lch 10
#define index n + 1
#define pozLin ll
#define ll 130 /* lățime linie de afișat */

#define true (1)
#define false (0)

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

FILE * fout;

typedef unsigned char boolean;

/*definire tip referinţă la un nod al cozii*/
typedef struct tip_nod * tip_referinta_nod;
/*definire tip nod al cozii*/
typedef struct tip_nod {
  ref element;
  tip_referinta_nod urm;
}
tip_nod;

/* Definirea structurii de date tip_coada}*/
typedef struct tip_coada {
  tip_referinta_nod inceput, spate;
}
tip_coada;

void initializeaza(tip_coada * c)
/*creaza coada vida c*/
{
  c -> inceput = (tip_nod * ) malloc(sizeof(tip_nod));
  /*crează nodul fictiv*/
  c -> inceput -> urm = NULL;
  c -> spate = c -> inceput;
  /*nodul fictiv este primul şi ultimul nod al cozii*/
} /*initializeaza*/

boolean vid(tip_coada c)
/*returnează true dacă coada este vidă, false altfel*/
{
  boolean vid_result;
  if (c.inceput == c.spate)
    vid_result = true;
  else vid_result = false;
  return vid_result;
} /*vid*/
ref cap(tip_coada c)
/*returnează elementul din capul cozii, sau semnalează eroare dacă coada este vidă*/
{
  ref cap_result;
  if (vid(c)) {
    return NULL;
  } else
    cap_result = c.inceput -> urm -> element;
  return cap_result;
} /*cap*/
void adauga(ref x, tip_coada * c)
/*adaugă un element la spatele cozii*/
{
  if (x != NULL) {
    c -> spate -> urm = (tip_nod * ) malloc(sizeof(tip_nod));
    /*se adaugă un nod nou la spatele cozii*/
    c -> spate = c -> spate -> urm;
    c -> spate -> element = x;
    c -> spate -> urm = NULL;
  }

} /*adauga*/
void scoate(tip_coada * c)
/*suprimă primul element al cozii, sau semnalează eroare
dacă coada este vidă*/
{
  if (vid( * c) == false) {
    c -> inceput = c -> inceput -> urm;
  }

} /*scoate*/

int DrumArbEch(int i, int j) {
  /* Generează în manieră recursivă matricea r corespunzătoare
  arborelui perfect echilibrat care poate fi construit
  utilizând cele n chei date şi returnează lungimea drumului
  acestui arbore */

  int k;
  k = (i + j + 1) / 2;
  r[i][j] = k; /* k este cheia mediană */
  if (i >= j)
    return b[k];
  else return DrumArbEch(i, k - 1) + DrumArbEch(k, j) + w[i][j];
} /* DrumArbEch */

void ArbOpt() {
  /* Construieşte arborele binar optim pornind de la matricea w a
  ponderilor nodurilor. De fapt se generează matricea r cu
  indicii cheilor care reprezintă rădăcinile subarborilor
  optimi şi matricea p cu lungimile corespunzătoare ale
  drumurilor asociate */

  int x, min;
  int i, j, k, h, m;

  for (i = 0; i <= n; i++)
    p[i][i] = w[i][i];
  for (i = 0; i <= n - 1; i++) {
    j = i + 1;
    p[i][j] = p[i][i] + p[j][j] + w[i][j];
    r[i][j] = j;
  }
  for (h = 2; h <= n; h++) {
    for (i = 0; i <= n - h; i++) {
      j = i + h;
      m = r[i][j - 1];
      min = p[i][m - 1] + p[m][j];
      for (k = m + 1; k <= r[i + 1][j]; k++) {
        x = p[i][k - 1] + p[k][j];
        if (x < min) {
          m = k;
          min = x;
        }
      }
      p[i][j] = min + w[i][j];
      r[i][j] = m;
    }
  }
} /* ArboreOpt */

ref Arbore(int i, int j, int * k) {
  /* Generează structura de date corespunzătoare arborelui
  optim. Porneşte de la matricea r care conţine rădăcinile
  subarborilor binari optimi si returnează referinţa la
  rădăcina arborelui optim construit */

  ref p;
  if (i == j) p = NULL;
  else {
    p = (ref) calloc(1, sizeof(nod));
    p -> sting = Arbore(i, r[i][j] - 1, k);
    p -> poz = (((ll - lch) * ( * k)) / (n - 1)) + (lch / 2);
    * k = * k + 1;
    strcpy(p -> cheie, chei[r[i][j]]);
    p -> drept = Arbore(r[i][j], j, k);
  }
  return p;
}

void AfiseazaArbore() {
  /* Realizează afişarea efectivă a structurii arborelui şi are
  drept parametri de intrare indicii i şi j care delimitează
  arborele de afişat */

  ref radacina;
  tip_coada curent, urm;
  ref q, q1, q2;
  int i, k;
  int u, u1, u2, u3, u4;

  k = 0;
  radacina = Arbore(0, n, & k);
  initializeaza( & curent);
  adauga(radacina, & curent);
  radacina -> leg = NULL;
  initializeaza( & urm);
  while (vid(curent) == false) {
    /* se afişează liniile verticale de legătură între
    niveluri pentru toate cuvintele din linia curentă */
    for (i = 1; i <= 3; i++) {
      u = 0;
      tip_coada aux = curent;
      do {
        q = cap(aux);
        int u1 = q -> poz;
        do {
          fprintf(fout, " ");
          u = u + 1;
        } while (u != u1);
        fprintf(fout, "I");
        u = u + 1;
        scoate( & aux);
      } while (vid(aux) == false);
      fprintf(fout, "\n");
    }

    /* se afişează linia curentă; se determină descendenţii
    nodurilor din lista curent şi se formează lista
    rândului următor urm */

    u = 0;
    do {
      q = cap(curent);
      int i = lch - 1;
      while (q -> cheie[i] == '\0') i = i - 1; /* lungime cheie */
      u2 = q -> poz - ((i - 1) / 2);
      u3 = u2 + i + 1;
      q1 = q -> sting;
      q2 = q -> drept;
      if (q1 == NULL)
        u1 = u2;
      else {
        u1 = q1 -> poz;
        adauga(q1, & urm);
      }
      if (q2 == NULL)
        u4 = u3;
      else {
        u4 = q2 -> poz + 1;
        adauga(q2, & urm);
      }
      i = -1;
      while (u < u1) {
        fprintf(fout, " ");
        u = u + 1;
      }
      while (u < u2) {
        fprintf(fout, "-");
        u = u + 1;
      }
      while (u < u3) {
        i = i + 1;
        fprintf(fout, "%c", q -> cheie[i]);
        u = u + 1;
      }
      while (u < u4) {
        fprintf(fout, "-");
        u = u + 1;
      }
      scoate( & curent);
    } while (vid(curent) == false);
    fprintf(fout, "\n");
    /*se inversează lista urm și se face curentă*/
    initializeaza( & curent);
    while (vid(urm) == false) {
      q = cap(urm);
      scoate( & urm);
      adauga(q, & curent);
    }
  } /* WHILE */

}

int main(int argc, char * argv[]) {
  /* Programul principal - ReprezentareArbore */
  /* se iniţializează static tabela de chei */

  strcpy(chei[1], "ARRAY");
  strcpy(chei[2], "BEGIN");
  strcpy(chei[3], "CASE");
  strcpy(chei[4], "CONST");
  strcpy(chei[5], "DIV");
  strcpy(chei[6], "DOWNTO");
  strcpy(chei[7], "DO");
  strcpy(chei[8], "ELSE");
  strcpy(chei[9], "END");
  strcpy(chei[10], "FILE");
  strcpy(chei[11], "FOR");
  strcpy(chei[12], "FUNCTION");
  strcpy(chei[13], "GOTO");
  strcpy(chei[14], "IF");
  strcpy(chei[15], "IN");
  strcpy(chei[16], "LABEL");
  strcpy(chei[17], "MOD");
  strcpy(chei[18], "NIL");
  strcpy(chei[19], "OF");
  strcpy(chei[20], "PROCEDURE");
  strcpy(chei[21], "PROGRAM");
  strcpy(chei[22], "RECORD");
  strcpy(chei[23], "REPEAT");
  strcpy(chei[24], "SET");
  strcpy(chei[25], "THEN");
  strcpy(chei[26], "TO");
  strcpy(chei[27], "TYPE");
  strcpy(chei[28], "UNTIL");
  strcpy(chei[29], "VAR");
  strcpy(chei[30], "WHILE");
  strcpy(chei[31], "WITH");

  for (int i = 1; i <= n; i++) {
    /* se inițializează a și b */
    a[i] = 0;
    b[i] = 0;
  }
  b[0] = 0;
  k2 = lch;
  strcpy(litere, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
  strcpy(cifre, "0123456789");

  /* se balează textul de intrare, se identifică cheile şi
  identificatorii şi se determină a şi b */

  FILE * fis = fopen("pascal.txt", "r");
  if (!fis) {
    fprintf(stderr, "Eroare la deschiderea fisierului de intrare\n");
    exit(EXIT_FAILURE);
  }

  fout = fopen("rezultat.txt", "w");
  if (!fout) {
    fprintf(stderr, "Eroare la crearea fisierului de iesire\n");
    exit(EXIT_FAILURE);
  }

  do {

    ch = fgetc(fis);
    if (strchr(litere, ch)) {
      k1 = -1;
      do {
        if (k1 < lch) {
          k1 = k1 + 1;
          id[k1] = ch;
        }

        ch = fgetc(fis);
      } while (strchr(litere, ch) || strchr(cifre, ch));

      if (k1 >= k2)
        k2 = k1;
      else
        do {
          id[k2] = '\0';
          k2 = k2 - 1;
        } while (k2 != k1);
      i = 1, j = n;

      do {
        k = (i + j) / 2;
        if (strcmp(chei[k], id) <= 0) i = k + 1;
        if (strcmp(chei[k], id) >= 0) j = k - 1;
      } while (i <= j);

      if (strcmp(chei[k], id) == 0)
        a[k] = a[k] + 1;
      else {
        k = (i + j) / 2;
        b[k] = b[k] + 1;
      }
    } else
    if (ch == '\'')
      do {
        ch = fgetc(fis);
      } while (ch != '\'');
    else
    if (ch == '{')
      do {
        ch = fgetc(fis);
      } while (ch != '}');
  } while (ch != '$'); /* caracter sfârșit text sursă */
  fclose(fis);
  /* pentru fiecare cuvant cheie se afișează frecvențele a și b */
  fprintf(fout, "Cuvintele cheie si frecventele lor de aparitie\n");
  suma = 0;
  sumb = b[0];

  for (int i = 1; i <= n; i++) {
    suma = suma + a[i];
    sumb = sumb + b[i];
    fprintf(fout, "%-5d%-5d%-11s%c\n", b[i - 1], a[i], chei[i], chei[i][0]);

  }
  /* se afişează suma frecvenţelor de acces pentru a şi b */
  fprintf(fout, "%-5d\n", b[n]);
  fprintf(fout, "--- ---\n");
  fprintf(fout, "%-5d%-5d\n", sumb, suma);
  /* se calculează matricea w din a și b */
  for (int i = 0; i <= n; i++) {
    w[i][i] = b[i];
    for (j = i + 1; j <= n; j++) {
      w[i][j] = w[i][j - 1] + a[j] + b[j];
    }
  }
  /* se construiește și se afișează arborele perfect echilibrat
  cu limitele de 0 și n */
  fprintf(fout, "\n\n");
  fprintf(fout, "      lungimea medie a drumului arborelui echilibrat =%f\n", ((float) DrumArbEch(0, n)) / w[0][n]);
  AfiseazaArbore();
  /* se construiește și se afișează arborele optim cu limitele 0 și n */
  ArbOpt();
  fprintf(fout, "\n\n");
  fprintf(fout, "      lungimea medie a drumului arborelui Optim =%f\n", ((float) p[0][n]) / w[0][n]);
  AfiseazaArbore();
  /* se recalculează w considerând numai cuvintele-cheie, adica făcând b=0 */
  for (int i = 0; i <= n; i++) {
    w[i][i] = 0;
    for (int j = i + 1; j <= n; j++)
      w[i][j] = w[i][j - 1] + a[j];
  }
  /* se construiește și se afisează arborele optim cu limitele 0 și n care nu conține decât cuvintele cheie */
  ArbOpt();
  fprintf(fout, "\n\n");
  fprintf(fout, "      arborele optim considerand numai cuvintele-cheie\n");
  AfiseazaArbore();
  printf("Succes. Fisierul de iesire a fost creat si poate fi vizualizat: rezultat.txt");
  return 0;
}
