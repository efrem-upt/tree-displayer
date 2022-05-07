#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "displayer.h"
#include "coada.c"

FILE * fout; /* fisier de iesire */

int DrumArbEch(int i, int j) {
  int k;
  k = (i + j + 1) / 2;
  r[i][j] = k; /* k este cheia mediană */
  if (i >= j)
    return b[k];
  else return DrumArbEch(i, k - 1) + DrumArbEch(k, j) + w[i][j];
} /* DrumArbEch */

void ArbOpt() {
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
