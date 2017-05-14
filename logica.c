#include "logica.h"


void LOGICA_generarFichas(ListaPDI * l) {
  int i, j, u;
  Ficha_inserir fichas[28];
  //Ficha f;

  //creamos array con fichas(demomento estatico)
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
  //inserimos las fichas que estaban en estatico a la estructura lineal.
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
void LOGICA_robarFichaYMostrarla(ListaPDI * l, ListaPDI * lista_jugadores, int i) {
  Ficha aux;
  int c;
  LISTAPDI_irInicio(l);
  LISTAPDI_irInicio(&lista_jugadores[i]);
  aux = LISTAPDI_consultar(*l);
  LISTAPDI_borrar(l);
  LISTAPDI_inserir(&lista_jugadores[i], aux);
  printf(SE_HA_ROBADO_FICHA_X, aux.cara1, aux.cara2);

  fflushnou();
  system ("/bin/stty raw");
  c = getchar();
  system ("/bin/stty cooked");
  fflushnou();
  printf("\n");

}
int LOGICA_asignarGanador(ListaPDI* lista_jugadores, Player * players ,int num_players){
  int hay_domino[4];
  int i;
  int fin = 0;
    for(i = 0; i < num_players; i++) {
      hay_domino[i] = 0;
      if(LISTAPDI_estaVacia(lista_jugadores[i]) == 1) {
        hay_domino[i] = 1;
        printf("\n\n%s ha hecho domino!!\n\n", players[i].nombre);
        fin = 1;
      }
    }

  return fin;

}

int LOGICA_hayGanador(ListaPDI * lista_jugadores, Player * players, int num_players, int pasar_turno) {
  int fin, minima,i,u;
  int sumatorio_fichas[4];
  fin = 0;
  if(pasar_turno == 4) {
    fin = 1;
    for(i = 0; i < num_players; i++) {
      sumatorio_fichas[i] = 0;
      //Si llegamos aqui es porque se ha pasado turno 4 veces. Hallaremos el valor minimo de las dichas
      while(LISTAPDI_estaVacia(lista_jugadores[i]) == 0) {
        sumatorio_fichas[i] = sumatorio_fichas[i] + LISTAPDI_consultar(lista_jugadores[i]).cara1 + LISTAPDI_consultar(lista_jugadores[i]).cara2;
        LISTAPDI_avanzar(&lista_jugadores[i]);
      }
    }
    i = 0;
    minima = sumatorio_fichas[0];
    while(i<num_players) {
      if(sumatorio_fichas[i]<minima) {
        minima = sumatorio_fichas[i];
        u = i;
      }
    }
    printf("Como todos han pasado turno, el ganador es %s por tener menos fichas\n", players[u].nombre);
  }
  return fin;
}

void LOGICA_pintarTablero(ListaPDI * l) {
  Ficha f;
  LISTAPDI_irInicio(l);
  printf("Tablero: ");
  while(LISTAPDI_final(*l) == 0){
    f = LISTAPDI_consultar(*l);
    printf("[%d|%d] ", f.cara1, f.cara2);
    LISTAPDI_avanzar(l);

  }
  printf("\n\n");

}

void LOGICA_dinamicaJuego(ListaPDI * l, ListaPDI * lista_jugadores, ListaPDI * tablero , Player * players, int num_players) {
  int fin = 0;
  int i;
  int pasar_turno = 0;
  //La variable flag fin, hara ue en el momento que valga distinto de cero el juego acabe
  while(fin == 0) {
    i = 0;

    fin = LOGICA_hayGanador(lista_jugadores, players ,num_players ,pasar_turno);

    //pasar turno = 0 en cada ronda solo si los 4 lo pulsan acabaremos partida
    pasar_turno = 0;
    while(i < num_players && fin == 0) {
      //PRINTAR SOLO UNA FICHA.
      LOGICA_pintarTablero(tablero);
      printf("Fichas %s:\n", players[i].nombre);
      LOGICA_mostrarFichasJugador(lista_jugadores,l,tablero,i,&pasar_turno);
      system("clear");
      fin = LOGICA_asignarGanador(lista_jugadores, players, num_players);
      i++;
    }
  }
}

int LOGICA_sePuedeColocarFicha(ListaPDI * l, Ficha f) {
  int ok = 0;
  //dependiendo de ok, sabremos si es posible colocar la ficha o no
  Ficha aux;
  LISTAPDI_irInicio(l);
  aux = LISTAPDI_consultar(*l);
  if (aux.cara1 == f.cara1 || aux.cara1 == f.cara2 || aux.cara2 == f.cara1 || aux.cara2 == f.cara2) {
    ok = 1;

  }

  aux = LISTAPDI_consultarFinalLista(l);

  if (aux.cara1 == f.cara1 || aux.cara1 == f.cara2 || aux.cara2 == f.cara1 || aux.cara2 == f.cara2) {
    ok = ok + 2;

  }
  //ok por tanto solo podra valer 1, 2 o 3. 3 valdra cuando pueda inserir a la dcha y izq.
  return ok;
}
void LOGICA_mostrarFichasJugador(ListaPDI * lista_jugadores ,ListaPDI * l, ListaPDI * tablero ,int i, int * pasar_turno) {
  Ficha f;
  int ok;
  int contador_flecha = 0;
  int opcion;
  int j = 0;
  LISTAPDI_irInicio(&lista_jugadores[i]);
  //Printa una por una las fichas del jugador
  while(LISTAPDI_final(lista_jugadores[i]) == 0) {
    f = LISTAPDI_consultar(lista_jugadores[i]);
    ok = LOGICA_sePuedeColocarFicha(tablero, f);
    if (ok > 0) {
      printf("\t%d- [%d|%d] -> \n", j+1, f.cara1, f.cara2);
      contador_flecha++;
    }
    else {
      printf("\t%d- [%d|%d]\n", j+1, f.cara1, f.cara2);
    }
    LISTAPDI_avanzar(&lista_jugadores[i]);
    j++;
  }
  //Modificar el contar ficha
  LOGICA_llevarOpcionATablero(l,lista_jugadores, tablero ,opcion, i, j, contador_flecha, &pasar_turno);
  LISTAPDI_irInicio(lista_jugadores);
}

void LOGICA_inserirIzq(ListaPDI * tablero, ListaPDI * lista_jugadores, Ficha f, int i) {
  LISTAPDI_irInicio(tablero);
  LISTAPDI_inserir(tablero, f);
  LISTAPDI_borrar(&lista_jugadores[i]);

}

void LOGICA_inserirDcha(ListaPDI * tablero, ListaPDI * lista_jugadores, Ficha f,int i) {
  Ficha aux;
  aux = LISTAPDI_consultarFinalLista(tablero);
  LISTAPDI_inserir(tablero, f);
  LISTAPDI_borrar(&lista_jugadores[i]);
}

void LOGICA_preguntarOpcion(int * opcion, const texto[30]){
  printf("%s", texto);
  fflushnou();
  scanf("%d", opcion);
  fflushnou();

}
void LOGICA_llevarOpcionATablero(ListaPDI * l, ListaPDI * lista_jugadores, ListaPDI * tablero,int opcion, int i, int j, int contador_flecha, int * pasar_turno) {
  int u = 0;
  int ok = 0;
  Ficha f, aux;
  if(contador_flecha == 0 && LISTAPDI_estaVacia(*l) == 0){
    j++;
    printf("\t%d- Robar Ficha\n", j);
  }
  //Se printara pasar turno si y solo si no se tiran fichas y y el monton esta vacio
  if(contador_flecha == 0 && LISTAPDI_estaVacia(*l) == 1){
    j++;
    printf("\t%d- Pasar Turno\n", j);
    *pasar_turno++;
  }
  do {
      //Comprueba que la ficha que seleccionas este en el intervalo
      do {
        LOGICA_preguntarOpcion(&opcion, "Opcion Ficha: ");
        if (opcion>j) {
          printf("%s\n", ERROR_OPCION_MAXIMO_PERMITIDO);
        }
      }while(opcion > j);

      LISTAPDI_irInicio(&lista_jugadores[i]);
      while (u<opcion-1) {
        LISTAPDI_avanzar(&lista_jugadores[i]);
        u++;
      }
      f = LISTAPDI_consultar(lista_jugadores[i]);
      ok = LOGICA_sePuedeColocarFicha(tablero, f);

    if(ok == 0 && contador_flecha > 0){
      printf("%s\n", ERROR_OPCION_FICHA_VALIDA );
    }
    fflushnou();
    //Si hay fichas que tirar y la ficha que seleccionas no se puede colocar, repites bucle
  }while (contador_flecha > 0 && ok == 0);
  LOGICA_insertarLugarCorrespondiente(tablero, lista_jugadores,l ,f, ok ,i, j, pasar_turno);
}

void LOGICA_insertarLugarCorrespondiente(ListaPDI * tablero, ListaPDI* lista_jugadores, ListaPDI* l, Ficha f, int ok ,int i, int j, int * pasar_turno) {
  int izq_dcha;
  //La unica posibilidad aqui de que ok valga cero es que el usuario haya pulsado robar ficha o pasar turno
  if(ok == 0) {
    if(LISTAPDI_estaVacia(*l) == 0) {
      LOGICA_robarFichaYMostrarla(l,lista_jugadores,i);
    }
    else {
      *pasar_turno++;
    }

  }
  if (ok == 1) {
    LOGICA_inserirIzq(tablero, lista_jugadores,f,i);
  }
  if (ok == 2) {
    LOGICA_inserirDcha(tablero, lista_jugadores, f,i);
  }
  //Si ok vale 3, preguntaremos al usuario donde quiere inserir
  if(ok == 3){
    do {
      LOGICA_preguntarOpcion(&izq_dcha, MENU_IZQ_DCHA);
    } while (izq_dcha != 1 && izq_dcha != 2);
    if (izq_dcha == 1) {
      LOGICA_inserirIzq(tablero, lista_jugadores,f,i);
    }
    else {
      LOGICA_inserirDcha(tablero, lista_jugadores, f,i);

    }
  }
}
