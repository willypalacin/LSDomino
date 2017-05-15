#include "ranking.h"


void RANKING_abrirFichero () {
  FILE * fichero;
  int num_jugadores;

  fichero = fopen ("ranking.bin", "rb");
  if (fichero == NULL){
    fflush(stdout);
    printf ("%s\n", ERROR_FICHERO);
  }
  else{
    fread (&num_jugadores, sizeof(int), 1, fichero);
    if (num_jugadores > 0) {
      RANKING_crearEstructura (fichero, num_jugadores);

    }
    else {
      printf("%s\n", FICHERO_VACIO);
    }
    fclose (fichero);
  }
}

void RANKING_printarDatos (Jugador j, Extra_info extra){
  printf("\n");
  printf ("Jugador: %s\n", j.nombre);
  printf ("P.Ganadas: %d\n", j.p_ganadas);
  printf ("P.Perdidas: %d\n", j.p_perdidas);
  printf ("P.Totales: %d\n", extra.p_totales);
  printf ("Win Rate: %.2f%%\n", extra.win_rate);
  printf("\n");

}


void RANKING_escribirEnFichero(Jugador *jugadores,int num_jugadores) {
  FILE * fichero = fopen("ranking.bin", "wb");
  int i = 0;
  fwrite (&num_jugadores, sizeof(int), 1, fichero);
  while(i<num_jugadores) {
    fwrite (jugadores[i].nombre, sizeof(char), 20, fichero);
    fwrite (&jugadores[i].p_ganadas, sizeof(int), 1, fichero);
    fwrite (&jugadores[i].p_perdidas, sizeof(int), 1, fichero);

    i++;
  }
  fclose(fichero);

}

void RANKING_jugadoresAEstructura(Player * players, Jugador * jugadores,int  num_players, int num_jugs_ranking, int u) {
  Jugador * aux_jugs;
  Extra_info * extra_info;
  int i, j, contador;
  int no_repetido = 0;
  Jugador temporal[50];
  if(num_jugs_ranking == 0) {

    aux_jugs = (Jugador*) malloc (sizeof(Jugador)* num_players);
    if(aux_jugs != NULL) {
      extra_info = (Extra_info*)malloc (sizeof(Extra_info) * num_players);
      if(extra_info!= NULL) {
        for(i = 0; i<num_players; i++){

          aux_jugs[i].nombre = (char *) malloc (sizeof(char) * (strlen(players[i].nombre)+1));
          strcpy(aux_jugs[i].nombre, players[i].nombre);
          if(i==u) {
            aux_jugs[i].p_ganadas = 1;
            aux_jugs[i].p_perdidas = 0;
          }
          else {
            aux_jugs[i].p_ganadas = 0;
            aux_jugs[i].p_perdidas = 1;

          }
          extra_info[i].p_totales = aux_jugs[i].p_ganadas + aux_jugs[i].p_perdidas;
          extra_info[i].win_rate = (((float)aux_jugs[i].p_ganadas /(float) extra_info[i].p_totales) * 100);
        }


      }

    }
    RANKING_escribirEnFichero(aux_jugs,num_players);
  }
  else {
    contador = 0;
    for(i = 0; i < num_players; i++) {
      for(j = 0; j < num_jugs_ranking; j++) {
        if(strcmp(jugadores[j].nombre,players[i].nombre) == 0) {
          printf("ENTRA\n");
          strcpy(temporal[contador].nombre,jugadores[j].nombre);
          temporal[contador].p_ganadas = jugadores[j].p_ganadas;
          temporal[contador].p_perdidas = jugadores[j].p_perdidas;

          }
          else {
            strcpy(temporal[contador].nombre, players[j].nombre);
            temporal[contador].p_ganadas = 0;
            temporal[contador].p_perdidas = 0;
            no_repetido++;
          }
          if(contador == u) {
            temporal[contador].p_ganadas++;
          }
          else{
            temporal[contador].p_perdidas++;

          }
          contador++;
        }
      }
      RANKING_escribirEnFichero(temporal,contador);
    }
}

Jugador * RANKING_cargarEstructura(int * num_jugs_ranking) {
    int aux;
    FILE * f = fopen("ranking.bin", "r");
    Jugador * jugadores;
    fread (num_jugs_ranking, sizeof(int), 1, f);
    if(feof(f) == 1) {
      *num_jugs_ranking = 0;
    }
    else{
      jugadores = (Jugador *) malloc (sizeof (Jugador) * (*num_jugs_ranking));
      if (jugadores == NULL){
          printf("%s\n", ERROR_MEMORIA);
      }
    }
    fclose(f);
    return jugadores;
}

void RANKING_almacenoJugadores(Jugador * jugadores, int num_jugs_ranking) {
  FILE * fichero = fopen("ranking.bin", "r");
  int i;
  char aux[20];
  fread (&i, sizeof(int), 1, fichero);
  jugadores = (Jugador *) malloc (sizeof (Jugador) * num_jugs_ranking);
  if (jugadores == NULL){
    printf("%s\n", ERROR_MEMORIA);
  }
  else {

    for (i = 0; i < num_jugs_ranking; i++) {
      fread (aux, sizeof(char), 20, fichero);

      jugadores[i].nombre = (char *)malloc(sizeof(char) * (strlen(aux)+1));
      strcpy(jugadores[i].nombre,aux);

      aux[0] = '\0';

      }

  }
  fclose(fichero);
}

int RANKING_elegirOrden() {
  int orden;
  do {
    printf("%s","\n");
    printf("%s\n %s\n %s\n",MOSTRAR_POSIBILIDADES,ORDEN_ALFABETICO,ORDEN_WIN_RATE);
    printf("%s", OPCION_PARA_ORDENAR);
    fflushnou();
    scanf("%d", &orden);
    if (orden != 1 && orden !=2) {
        printf("%s\n", ERROR_WIN_RATE);
    }
  } while(orden != 1 && orden !=2);
  return orden;

}

void RANKING_ordenarAlfabetico (Jugador * jugadores, Extra_info * extra_info ,int n) {
  int i, j;
  Jugador tmp;
  Extra_info tmp2;
    for (i = 0 ; i < ( n - 1 ); i++) {
      for (j = 0 ; j < n - i - 1; j++) {
        if (strcmp(jugadores[j].nombre,jugadores[j+1].nombre) > 0) {
          tmp = jugadores[j];
          jugadores[j] = jugadores[j+1];
          jugadores[j+1] = tmp;

          tmp2 = extra_info[j];
          extra_info[j] = extra_info[j + 1];
          extra_info[j+1] = tmp2;

        }
      }
    }
}

void RANKING_ordenWinRate (Jugador * jugadores, Extra_info * extra_info ,int num_jugadores) {
	int i, j;
	Jugador tmp;
	Extra_info tmp2;

	for (i = 0; i < num_jugadores; i++) {
		for (j = num_jugadores - 1; j >= i; j--) {

			if (extra_info[j].win_rate < extra_info[j-1].win_rate) {

				tmp = jugadores[j];
				jugadores[j] = jugadores[j-1];
				jugadores[j-1] = tmp;

  			tmp2 = extra_info[j];
  			extra_info[j] = extra_info[j - 1];
      	extra_info[j-1] = tmp2;
        printf("%s","\n");

			}
		}
	}


}

void RANKING_crearEstructura (FILE * fichero, int num_jugadores){
  Jugador * jugadores;
  int i;
  Extra_info * extra_info;
  int opcion_orden;
  jugadores = (Jugador *) malloc (sizeof (Jugador) * num_jugadores);
  if (jugadores == NULL){
    printf("%s\n", ERROR_MEMORIA);
  }
  else {
    extra_info = (Extra_info *) malloc (sizeof(Extra_info) * num_jugadores);
    if (extra_info == NULL){
      printf("%s\n", ERROR_MEMORIA_2);
    }
    else {

      for (i = 0; i < num_jugadores; i++) {
        fread (&jugadores[i], sizeof(Jugador), 1, fichero);
        extra_info[i].p_totales = jugadores[i].p_ganadas + jugadores[i].p_perdidas;
        extra_info[i].win_rate = (((float)jugadores[i].p_ganadas /(float) extra_info[i].p_totales) * 100);


        }
        opcion_orden = RANKING_elegirOrden();
        //ESTE SWITCH LO METERIA EN UNA FUNCION APARTE FUNCION DEMASIADO GRANDE
        switch (opcion_orden) {
          case 1:

            RANKING_ordenarAlfabetico(jugadores,extra_info, num_jugadores);
            for (i = 0; i < num_jugadores; i++) {
              RANKING_printarDatos (jugadores[i], extra_info[i]);
            }
            break;
          case 2:
            RANKING_ordenWinRate (jugadores, extra_info, num_jugadores);
            for (i = 0; i < num_jugadores; i++) {
              RANKING_printarDatos (jugadores[i], extra_info[i]);
            }
            break;
          default:
            printf("%s\n", MENSAJE_ERROR_OPCION);
            break;
      }
    }
  }
}
