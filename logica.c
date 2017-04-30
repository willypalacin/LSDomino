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

void LOGICA_fichasRandom(ListaPDI * l) {
  int numero_random;
  int i,j,u;
  Ficha aux;
  i = 0;
  while(i < 29) {
    LISTAPDI_irInicio(l);
    for(u = 0; u< i-1; u++) {
      LISTAPDI_avanzar(l);

    }
    numero_random = (rand() % 28) - i;
    aux = LISTAPDI_consultar(*l);
    printf("%d\n", aux.cara1);
    LISTAPDI_borrar(l);
    for (j = 0; j<numero_random-1; j++) {
      LISTAPDI_avanzar(l);

    }
    LISTAPDI_inserir(l, aux);
    i++;

  }


}
