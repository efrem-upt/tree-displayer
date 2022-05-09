#include "resources\displayer.c"

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
  if (argc != 2) {
    fprintf(stderr, "Formatarea argumentelor incorecta. Programul accepta un singur argument care este path-ul fisierul fisierului text cu cod sursa Pascal");
    exit(EXIT_FAILURE);
  }
  FILE * fis = fopen(argv[1], "r");
  if (!fis) {
    fprintf(stderr, "Eroare la deschiderea fisierului de intrare\n");
    exit(EXIT_FAILURE);
  }
  char out[ffl + 1];
  strcpy(out, argv[1]);
  char * extension = strchr(out, '.');
  strcpy(extension + 1, "txt");
  fout = fopen(out, "w");
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
        if (stricmp(chei[k], id) <= 0) i = k + 1;
        if (stricmp(chei[k], id) >= 0) j = k - 1;
      } while (i <= j);

      if (stricmp(chei[k], id) == 0)
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
    else if (ch == '(') {
                ch = fgetc(fis);
                if (ch == '*') {
                    do {
                        do {
                        ch = fgetc(fis);
                        }while(ch != '*');
                        ch = fgetc(fis);
                    }while(ch != ')');
                } else ungetc(ch, fis);
        }
    else if (ch == '{')
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
  printf("Succes. Fisierul de iesire a fost creat si poate fi vizualizat: %s", out);
  return 0;
}
