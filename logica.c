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
  LOGICA_anadirFichasALista(l,fichas);
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

}

void LOGICA_anadirFichasALista (ListaPDI * l, Ficha_inserir fichas[28]) {
  int i,j;
  LISTAPDI_irInicio(l);
  for(i = 0; i < 28; i++) {
    LISTAPDI_inserir(l,fichas[i].f);

  }

}

void LOGICA_robarFicha(ListaPDI * l, ListaPDI * lista_jugadores, int i) {
  Ficha aux;
  LISTAPDI_irInicio(l);
  LISTAPDI_irInicio(&lista_jugadores[i]);
  aux = LISTAPDI_consultar(*l);
  LISTAPDI_borrar(l);
  LISTAPDI_inserir(&lista_jugadores[i], aux);

}

void LOGICA_pintarTablero(ListaPDI * l) {
  Ficha f;
  LISTAPDI_irInicio(l);
  printf("Tablero: ");
  while(LISTAPDI_final(*l) == 0){
    f = LISTAPDI_consultar(*l);
    printf("[%d|%d] ", f.cara1, f.cara2);
    LISTAPDI_avanzar (l);

  }
  printf("\n\n");

}
