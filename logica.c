#include "logica.h"


void LOGICA_generarFichas(ListaPDI * l) {
  int i, j, u;
  Ficha_inserir fichas[28];
  //Ficha f;

  //CREAMOS UN ARRAY CON LAS FICHAS
  u = 0;
  for (i = 0; i <= 6; i++) {
    for (j = i; j<= 6; j++) {
        fichas[u].f.cara1 = i;
        fichas[u].f.cara2 = j;
        fichas[u].inserida = 0;
        u++;
        //LISTAPDI_inserir(l, f);
    }

  }

  //ESTE ARRAY ESTA ORDENADO ASI QUE QUEREMOS DESORDENARLO.
  LOGICA_desordenarFichas(fichas);
  //LOGICA_fichasRandom(l,fichas)
}

void LOGICA_desordenarFichas(Ficha_inserir fichas[28]) {
  int i,u,j, numero_random;
  Ficha aux;
  u = 0;
  while(u < 28) {
    if (fichas[u].inserida == 0) {
      numero_random = (int) rand() % 28;
      aux = fichas[u].f;
      fichas[u].f = fichas[numero_random].f;
      fichas[numero_random].f = aux;

      fichas[numero_random].inserida = 1;
      fichas[u].inserida = 1;
      u++;
    }
    else {
      u++;
    }



  }

  u = 0;
  for(i = 0; i <= 6; i++) {
    printf("\n");
    for (j = i; j <= 6; j++) {
      printf("[%d|%d] ", fichas[u].f.cara1, fichas[u].f.cara2);
      u++;
    }
  }

}
//Rehacer el random
//void LOGICA_fichasRandom(ListaPDI * l, Ficha_inserir fichas[28]) {


  /*i = 0;
  while(i < 29) {
    for(u = 0; u <= i; u++) {
      LISTAPDI_avanzar(l);

    }
    do {
      numero_random = rand() % 29;
    }while(numero_random == i-1);
    aux = LISTAPDI_consultar(*l);
    //printf("%d\n", aux.cara1);
    LISTAPDI_borrar(l);
    LISTAPDI_irInicio(l);
    for (j = 0; j <= numero_random; j++) {
      LISTAPDI_avanzar(l);

    }
    LISTAPDI_inserir(l, aux);
    LISTAPDI_irInicio(l);

    i++;

  }


}*/
