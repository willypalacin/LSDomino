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
  int u, numero_random;
  Ficha aux;
  u = 0;
  srand(time(NULL));
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
  int i;
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
  LISTAPDI_irInicio(l);
  LISTAPDI_irInicio(&lista_jugadores[i]);
  aux = LISTAPDI_consultar(*l);
  LISTAPDI_borrar(l);
  LISTAPDI_inserir(&lista_jugadores[i], aux);
  printf(SE_HA_ROBADO_FICHA_X, aux.cara1, aux.cara2);

  fflushnou();
  system ("/bin/stty raw");
  getchar();
  system ("/bin/stty cooked");
  fflushnou();
  printf("\n");

}
int LOGICA_asignarGanador(ListaPDI* lista_jugadores, Player * players ,int num_players, Jugador * jugadores, int num_jugs_ranking, char ** argv){
  int i;
  int fin = 0;
    for(i = 0; i < num_players; i++) {
      if(LISTAPDI_estaVacia(lista_jugadores[i]) == 1) {
        printf("\n\n%s ha hecho domino!!\n\n", players[i].nombre);
        fin = 1;
        RANKING_jugadoresAEstructura(players, jugadores,num_players, num_jugs_ranking, i, argv);

      }
    }

  return fin;

}
int LOGICA_comprobarEmpate(int sumatorio_fichas[4], int jugs_empate[4], int num_players, int u) {
  int empate;
  int contador, i;
  for (i = 0; i<num_players; i++) {
    jugs_empate[i] = 0;
  }

  i = 0;
  empate = 0;
  contador = 0;
  while(i<num_players) {
    if(sumatorio_fichas[u] == sumatorio_fichas[i]) {
      jugs_empate[i] = 1;
      contador++;
    }
    else {

      jugs_empate[i] = 0;
    }
    i++;
  }
  if (contador > 1) {
    empate = 1;
  }

  return empate;

}

int LOGICA_hayGanador(ListaPDI * lista_jugadores, Player * players, Jugador * jugadores ,int num_players, int pasar_turno, int num_jugs_ranking, char ** argv) {
  int fin, minima,i,u;
  int sumatorio_fichas[4];
  int contador_fichas[4];
  int jugs_empate[4];
  int empate_menos_fichas = 0;
  int empate_sumatorio = 0;
  fin = 0;
  u = 0;

  if(pasar_turno == num_players) {
    fin = 1;
    for(i = 0; i < num_players; i++) {
      LISTAPDI_irInicio(&lista_jugadores[i]);
      sumatorio_fichas[i] = 0;
      contador_fichas[i] = 0;
      //Si llegamos aqui es porque se ha pasado turno 4 veces. Hallaremos quien tiene menos fichas
      while(LISTAPDI_final(lista_jugadores[i]) == 0) {
        contador_fichas[i]++;
        sumatorio_fichas[i] = sumatorio_fichas[i] + LISTAPDI_consultar(lista_jugadores[i]).cara1 + LISTAPDI_consultar(lista_jugadores[i]).cara2;
        LISTAPDI_avanzar(&lista_jugadores[i]);
      }
    }
    i = 0;
    minima = contador_fichas[0];
    while(i<num_players) {
      if(contador_fichas[i]<minima) {
        minima = contador_fichas[i];
        u = i;
      }
      i++;
    }
    //Voy a comprobar que no haya empate a la hora de ganar

    empate_menos_fichas = LOGICA_comprobarEmpate(contador_fichas, jugs_empate,num_players,u);

    if(empate_menos_fichas == 1) {

      i = 0;
      minima = sumatorio_fichas[0];
      while(i<num_players) {
        if(sumatorio_fichas[i]<minima) {
          minima = sumatorio_fichas[i];
          u = i;
        }
        i++;
      }

      empate_sumatorio = LOGICA_comprobarEmpate(sumatorio_fichas,jugs_empate,num_players, u);

      if (empate_sumatorio == 1) {

        if(jugs_empate[i] == 1) {
          printf(EMPATE);
          RANKING_jugadoresEmpate(players,jugadores,num_players, num_jugs_ranking, jugs_empate, argv);
        }
      }
      else {
        printf("Como todos han pasado turno y empatan numero de fichas, el ganador es %s por que sus fichas suman menos\n", players[u].nombre);
        RANKING_jugadoresAEstructura(players,jugadores,num_players, num_jugs_ranking, u, argv);
      }
    }
    else {
      printf("Como todos han pasado turno, el ganador es %s por tener menos fichas\n", players[u].nombre);
      RANKING_jugadoresAEstructura(players,jugadores,num_players, num_jugs_ranking, u, argv);

    }



  }
  return fin;
}

void LOGICA_pintarTablero(ListaPDI * l) {
  Ficha f;

  LISTAPDI_irInicio(l);
  printf("Tablero: ");

/*
  Ficha eliminar;
  eliminar.cara1 = 8;
  eliminar.cara2 = 8;
  LISTAPDI_inserir(l, eliminar);
*/

  while(LISTAPDI_final(*l) == 0){
    f = LISTAPDI_consultar(*l);
    printf("[%d|%d] ", f.cara1, f.cara2);
    LISTAPDI_avanzar(l);


  }
  printf("\n\n");
/*
  eliminar.cara1 = 8;
  eliminar.cara2 = 8;
  LISTAPDI_inserir(l, eliminar);
*/
}

void LOGICA_dinamicaJuego(ListaPDI * l, ListaPDI * lista_jugadores, ListaPDI * tablero , Player * players, int num_players, Jugador * jugadores, int num_jugs_ranking, char ** argv) {
  int fin = 0;
  int i;
  int pasar_turno = 0;
  //La variable flag fin, hara ue en el momento que valga distinto de cero el juego acabe
  while(fin == 0) {
    i = 0;

    pasar_turno = 0;

    while(i < num_players && fin == 0) {
      //PRINTAR SOLO UNA FICHA.
      LOGICA_pintarTablero(tablero);
      printf("Fichas %s:\n", players[i].nombre);
      LOGICA_mostrarFichasJugador(lista_jugadores,l,tablero,i,&pasar_turno);
      system("clear");
      fin = LOGICA_asignarGanador(lista_jugadores, players, num_players, jugadores, num_jugs_ranking, argv);
      if (fin == 0) {
        fin = LOGICA_hayGanador(lista_jugadores, players ,jugadores,num_players ,pasar_turno, num_jugs_ranking,argv);
      }
      i++;

    }
  }
  if (fin == 1) {
    LOGICA_liberaMemoria(&lista_jugadores, &players);
  }
}

int LOGICA_sePuedeColocarFicha(ListaPDI * l, Ficha f) {
  int ok = 0;
  //dependiendo de ok, sabremos si es posible colocar la ficha o no
  Ficha aux;
  LISTAPDI_irInicio(l);
  aux = LISTAPDI_consultar(*l);
  //Solo se podra colocar si mi ficha coincide con la cara1 de aux
  if (aux.cara1 == f.cara1 || aux.cara1 == f.cara2) {
    ok = 1;

  }

  aux = LISTAPDI_consultarFinalLista(l);
  //Solo se podra colocoar si cualquiera delas dos caras de la ficha del jugador coincide con la cara2 del tablero
  if (aux.cara2 == f.cara1 || aux.cara2 == f.cara2) {
    ok = ok + 2;

  }
  //ok por tanto solo podra valer 1, 2 o 3. 3 valdra cuando pueda inserir a la dcha y izq.
  return ok;
}
void LOGICA_mostrarFichasJugador(ListaPDI * lista_jugadores ,ListaPDI * l, ListaPDI * tablero ,int i, int * pasar_turno) {
  Ficha f;
  int ok;
  int contador_flecha = 0;
  int j = 0;
  LISTAPDI_irInicio(&lista_jugadores[i]);
  //Printa una por una las fichas del jugador
  while(LISTAPDI_final(lista_jugadores[i]) == 0) {
    f = LISTAPDI_consultar(lista_jugadores[i]);
    ok = LOGICA_sePuedeColocarFicha(tablero, f);
    if (ok > 0) {
      printf("\t%d- [%d|%d] -> \n", j+1, f.cara1, f.cara2);
      contador_flecha++;
      *pasar_turno = 0;
    }
    else {
      printf("\t%d- [%d|%d]\n", j+1, f.cara1, f.cara2);
    }
    LISTAPDI_avanzar(&lista_jugadores[i]);
    j++;
  }
  //Modificar el contar ficha
  LOGICA_llevarOpcionATablero(l,lista_jugadores, tablero, i, j, contador_flecha, pasar_turno);
  LISTAPDI_irInicio(lista_jugadores);
}

void LOGICA_inserirIzq(ListaPDI * tablero, ListaPDI * lista_jugadores, Ficha f, int i) {
  Ficha aux;
  LISTAPDI_irInicio(tablero);
  if(f.cara2  != LISTAPDI_consultar(*tablero).cara1){
    //Hago un SWAP
    aux.cara1 = f.cara2;
    f.cara2 = f.cara1;
    f.cara1 = aux.cara1;
  }
  LISTAPDI_inserir(tablero, f);
  LISTAPDI_borrar(&lista_jugadores[i]);

}

void LOGICA_inserirDcha(ListaPDI * tablero, ListaPDI * lista_jugadores, Ficha f,int i) {
  Ficha a;
  Ficha aux;
  a = LISTAPDI_consultarFinalLista(tablero);
  if(f.cara1  != a.cara2){
    //Hago un SWAP
    aux.cara1 = f.cara2;
    f.cara2 = f.cara1;
    f.cara1 = aux.cara1;
  }
  LISTAPDI_inserir(tablero, f);
  LISTAPDI_borrar(&lista_jugadores[i]);
}

void LOGICA_preguntarOpcion(int * opcion, char texto[30]){
  printf("%s", texto);
  fflushnou();
  scanf("%d",opcion);
  //scanf("%d", opcion);

  fflushnou();

}
void LOGICA_llevarOpcionATablero(ListaPDI * l, ListaPDI * lista_jugadores, ListaPDI * tablero, int i, int j, int contador_flecha, int * pasar_turno) {
  int u = 0;
  int robar = 0;
  int opcion;
  int ok = 0;
  int flag = 0;
  Ficha f;
  if(contador_flecha == 0 && LISTAPDI_estaVacia(*l) == 0){
    j++;
    printf("\t%d- Robar Ficha\n", j);
    robar++;
  }
  //Se printara pasar turno si y solo si no se tiran fichas y y el monton esta vacio
  if(contador_flecha == 0 && LISTAPDI_estaVacia(*l) == 1){
    j++;
    printf("\t%d- Pasar Turno\n", j);
    *pasar_turno = *pasar_turno + 1;
    robar++;
  }
  do {
      //Comprueba que la ficha que seleccionas este en el intervalo
      do {
        LOGICA_preguntarOpcion(&opcion, "Opcion Ficha: ");
        if (opcion>j) {
          printf("%s\n", ERROR_OPCION_MAXIMO_PERMITIDO);
        }
      }while(opcion > j);
      u = 0;
      LISTAPDI_irInicio(&lista_jugadores[i]);
      while (u<opcion-1) {
        LISTAPDI_avanzar(&lista_jugadores[i]);
        u++;
      }
      f = LISTAPDI_consultar(lista_jugadores[i]);
      ok = LOGICA_sePuedeColocarFicha(tablero, f);

      fflushnou();

      if(ok == 0 && opcion == j && robar == 1 ) {
        flag = 1;
      }
      if(ok == 0 && flag == 0) {
        printf("%s\n", ERROR_OPCION_FICHA_VALIDA );

      }
    //Si hay fichas que tirar y la ficha que seleccionas no se puede colocar, repites bucle
  }while (ok == 0 && flag == 0);
  LOGICA_insertarLugarCorrespondiente(tablero, lista_jugadores,l ,f, ok ,i);
}

void LOGICA_insertarLugarCorrespondiente(ListaPDI * tablero, ListaPDI* lista_jugadores, ListaPDI* l, Ficha f, int ok ,int i) {
  int izq_dcha;
  //La unica posibilidad aqui de que ok valga cero es que el usuario haya pulsado robar ficha o pasar turno
  if(ok == 0) {
    if(LISTAPDI_estaVacia(*l) == 0) {
      LOGICA_robarFichaYMostrarla(l,lista_jugadores,i);
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

void LOGICA_liberaMemoria(ListaPDI * *lista_jugadores, Player ** players) {
  free(*lista_jugadores);
  free(*players);

}
