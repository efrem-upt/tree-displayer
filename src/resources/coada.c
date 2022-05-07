#include "coada.h"
#include <stdlib.h>

void initializeaza(tip_coada * c) {
  c -> inceput = (tip_nod * ) malloc(sizeof(tip_nod));
  /*creazã nodul fictiv*/
  c -> inceput -> urm = NULL;
  c -> spate = c -> inceput;
  /*nodul fictiv este primul ºi ultimul nod al cozii*/
} /*initializeaza*/

boolean vid(tip_coada c) {
  boolean vid_result;
  if (c.inceput == c.spate)
    vid_result = true;
  else vid_result = false;
  return vid_result;
} /*vid*/

ref cap(tip_coada c) {
  ref cap_result;
  if (vid(c)) {
    return NULL;
  } else
    cap_result = c.inceput -> urm -> element;
  return cap_result;
} /*cap*/

void adauga(ref x, tip_coada * c) {
  if (x != NULL) {
    c -> spate -> urm = (tip_nod * ) malloc(sizeof(tip_nod));
    /*se adaugã un nod nou la spatele cozii*/
    c -> spate = c -> spate -> urm;
    c -> spate -> element = x;
    c -> spate -> urm = NULL;
  }

} /*adauga*/

void scoate(tip_coada * c) {
  if (vid( * c) == false) {
    c -> inceput = c -> inceput -> urm;
  }

} /*scoate*/
