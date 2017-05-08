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

void LOGICA_dinamicaJuego(ListaPDI * l, ListaPDI * lista_jugadores, Player * players, int num_players) {
  int fin = 0;
  int i;

  while(fin == 0) {
    i = 0;
    //AQUI COMPROBARIAMOS SI HAY GANADOR
    while(i < num_players) {
      //PRINTAR SOLO UNA FICHA.
      LOGICA_pintarTablero(l);
      printf("Fichas %s:\n", players[i].nombre);
      LOGICA_mostrarFichasJugador(lista_jugadores, l ,i);
      i++;
    }
  }
}

int LOGICA_sePuedeColocarFicha(ListaPDI * l, Ficha f) {
  int ok = 0;
  Ficha aux;
  LISTAPDI_irInicio(l);
  aux = LISTAPDI_consultar(*l);
  if (aux.cara1 == f.cara1 || aux.cara1 == f.cara2 || aux.cara2 == f.cara1 || aux.cara2 == f.cara2) {
    ok = 1;

  }

  aux = LISTAPDI_consultarFinalLista(l);

  if (aux.cara1 == f.cara1 || aux.cara1 == f.cara2 || aux.cara2 == f.cara1 || aux.cara2 == f.cara2) {
    ok = 2;

  }
  return ok;
}
void LOGICA_mostrarFichasJugador(ListaPDI * lista_jugadores, ListaPDI * l ,int i) {
  Ficha f;
  int ok;
  int opcion;
  int j = 0;
  LISTAPDI_irInicio(&lista_jugadores[i]);
  while(LISTAPDI_final(lista_jugadores[i]) == 0) {
    f = LISTAPDI_consultar(lista_jugadores[i]);
    ok = LOGICA_sePuedeColocarFicha(l, f);
    if (ok == 1 || ok == 2) {
      printf("\t%d- [%d|%d] -> \n", j+1, f.cara1, f.cara2);
    }
    else {
      printf("\t%d- [%d|%d]\n", j+1, f.cara1, f.cara2);
    }
    LISTAPDI_avanzar(&lista_jugadores[i]);


    j++;
  }
  //Modificar el contar ficha
  printf("\t%d- Robar Ficha\n", j+1);
  printf("\t%d- Pasar Turno\n", j+2);

  //Con el indice j implementas
  printf("Opcion ficha: ");
  scanf("%d", &opcion);
  LOGICA_llevarOpcionATablero(l,lista_jugadores, opcion, i, j);
  LISTAPDI_irInicio(lista_jugadores);


}

void LOGICA_llevarOpcionATablero(ListaPDI * l,ListaPDI * lista_jugadores, int opcion, int i, int j) {
  int u = 0;
  int ok = 0;
  Ficha f;
  Ficha aux;
  LISTAPDI_irInicio(&lista_jugadores[i]);
  while (u<opcion-1) {
    LISTAPDI_avanzar(&lista_jugadores[i]);
    u++;

  }
  f = LISTAPDI_consultar(lista_jugadores[i]);
  ok = LOGICA_sePuedeColocarFicha(l, f);
  if (ok == 1) {
    LISTAPDI_irInicio(l);
    LISTAPDI_inserir(l, f);
    LISTAPDI_borrar(&lista_jugadores[i]);

  }
  if (ok == 2) {
    aux = LISTAPDI_consultarFinalLista(l);
    LISTAPDI_inserir(l, f);
    LISTAPDI_borrar(&lista_jugadores[i]);

  }
  if (ok == 0 && (opcion != j+1 || opcion!= j+2)) {
    printf("\nTal y como esta indicado, no es posible pasar esta ficha. \nSe pasa turno por defecto\n\n");

  }
  if(opcion == j + 1) {
    printf("\nSe pasa turno\n\n");

  }
  if(opcion == j + 2) {
    printf("Se roba ficha\n\n");

  }




}
