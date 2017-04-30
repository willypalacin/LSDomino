#include "logica.h"

void LOGICA_generarFichas(ListaPDI * l) {
  int i, j;
  Ficha f;
  for (i = 0; i <= 6; i++) {
    for (j = i; j<= 6; j++) {
        f.cara1 = i;
        f.cara2 = j;
        LISTAPDI_inserir(l, f);


    }

  }


}
