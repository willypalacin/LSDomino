#include "ranking.h"



void RANKING_abrirFichero () {
  FILE * fichero;
  int num_jugadores;

  fichero = fopen ("ranking.bin", "rb");
  fread (&num_jugadores, sizeof(int), 1, fichero);
  if (feof(fichero) != 1) {
    RANKING_crearEstructura (fichero, num_jugadores);

  }
  else {
    printf("%s\n", FICHERO_VACIO);
  }
  fclose (fichero);
}

void RANKING_printarDatos (Jugador * j, Extra_info * extra, int num_jugadores){
  int i;
  for (i = 0; i<num_jugadores; i++) {
    printf("\n");
    printf ("Jugador: %s\n", j[i].nombre);
    printf ("P.Ganadas: %d\n", j[i].p_ganadas);
    printf ("P.Perdidas: %d\n", j[i].p_perdidas);
    printf ("P.Totales: %d\n", extra[i].p_totales);
    printf ("Win Rate: %.2f%%\n", extra[i].win_rate);
    printf("\n");
  }
}

void RANKING_escribirEnFichero(Jugador * jugadores,int num_jugadores) {
  int num;
  printf("%d\n",num_jugadores);
  printf("%s\n",jugadores[0].nombre);
  J jug[20];
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
  fichero = fopen("ranking.bin", "rb");
  i = 0;
  fread (&num, sizeof(int), 1, fichero);
  while (i<num_jugadores) {
    fread (jug[i].nombre, sizeof(char), 20, fichero);
    fread (&jug[i].p_g, sizeof(int), 1, fichero);
    fread (&jug[i].p_p, sizeof(int), 1, fichero);
    i++;
  }
  fclose(fichero);
  for(i = 0; i<num_jugadores; i++) {
    printf("%s\n", jug[i].nombre);
    printf("%d\n", jug[i].p_g);
    printf("%d\n", jug[i].p_p);
    printf("\n");
  }
}

void RANKING_jugadoresAEstructura(Player * players, Jugador * jugadores, int  num_players, int num_jugs_ranking, int u) {
  Jugador * aux_jugs;
  Extra_info * extra_info;
  int i, j, i_temp, contador,encontrado;
  int no_repetido = 0;
  Jugador * temporal;
  int inserido_player [50];
  int inserido_jug[50];
  for (i = 0; i<50; i++) {
    inserido_jug[i] = 0;
    inserido_player[i] = 0;
  }

  if(num_jugs_ranking == 0) {

    aux_jugs = (Jugador*) malloc (sizeof(Jugador)* num_players);
    if(aux_jugs != NULL) {
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
      }
      RANKING_escribirEnFichero(aux_jugs,num_players);

    }

  }
  else {
    contador = 0;

    printf("%s %s\n", jugadores[0].nombre, players[0].nombre);
    for(i = 0; i < num_players; i++) {
      for(j = 0; j < num_jugs_ranking; j++) {
        if( (strcmp(jugadores[j].nombre, players[i].nombre) == 0)) {

          contador++;

        }

      }
    }
    printf("%d\n", contador);
    i_temp = 0;
    temporal = (Jugador * )malloc(sizeof(Jugador) * (num_jugs_ranking + num_players - contador));
    for (i = 0; i < num_jugs_ranking; i++) {
      temporal[i] = jugadores[i];
      i_temp++;
    }

    printf("ITEMP 1 %d\n", i_temp);

    for(i = 0; i<num_players; i++) {
      encontrado = -1;
      for(j = 0; j < i_temp; j++) {
        if((strcmp(temporal[j].nombre, players[i].nombre)) == 0) {
          temporal[i_temp].nombre= (char*)malloc(sizeof(char)*(strlen(players[i].nombre)+1));
          strcpy(temporal[i_temp].nombre, players[i].nombre);
          encontrado = j;
          printf("PETA I_TEMP %d\n", i_temp);


        }
      }
      if(encontrado != -1) {
        if(strcmp(temporal[encontrado].nombre, players[u].nombre) == 0) {
          temporal[encontrado].p_ganadas++;
        }
        else {
          temporal[encontrado].p_perdidas++;
        }

      }
      else {
        strcpy(temporal[i_temp].nombre, players[i].nombre);
        if(strcmp(temporal[encontrado].nombre, players[u].nombre) == 0) {
          temporal[encontrado].p_ganadas = 1;
        }
        else {
          temporal[encontrado].p_perdidas = 0;
        }
        i_temp++;

      }

    }
    printf("ITEMP 2%d\n", i_temp);
    printf("EntraRKG\n");
    RANKING_escribirEnFichero(temporal,i_temp);

  }
}

void RANKING_numJugadoresIniciales(int * num_jugs_ranking) {
  int aux;
  FILE * f;
  Jugador * jugadores = NULL;
  f = fopen("ranking.bin", "rb");
  fread (num_jugs_ranking, sizeof(int), 1, f);
  if(feof(f) == 1) {
    *num_jugs_ranking = 0;
  }

  fclose(f);
}

void RANKING_almacenoJugadores(Jugador* *jugadores, int num_jugs_ranking) {
  FILE * fichero = fopen("ranking.bin", "rb");
  int i;
  char aux[20];
  fread (&i, sizeof(int), 1, fichero);
  *jugadores = (Jugador *) malloc (sizeof (Jugador) * num_jugs_ranking);
  if (jugadores == NULL){
    printf("%s\n", ERROR_MEMORIA);
  }
  else {

    for (i = 0; i < num_jugs_ranking; i++) {
      fread (aux, sizeof(char), 20, fichero);

      (*jugadores)[i].nombre = (char *)malloc(sizeof(char) * (strlen(aux)+1));
      strcpy((*jugadores)[i].nombre,aux);
      fread (&(*jugadores)[i].p_ganadas, sizeof(int), 1, fichero);
      fread (&(*jugadores)[i].p_perdidas, sizeof(int), 1, fichero);
      printf("%s\n %d\n %d\n", (*jugadores)[i].nombre, (*jugadores)[i].p_ganadas, (*jugadores)[i].p_perdidas );
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

void RANKING_ordenarAlfabetico (Jugador * jugadores, Extra_info * extra_info, int n) {
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
  char aux_nombre[20];
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


        fread (aux_nombre, sizeof(char), 20, fichero);
        jugadores[i].nombre = (char*)malloc (sizeof(char) * (strlen(aux_nombre)+1));
        strcpy(jugadores[i].nombre, aux_nombre);
        fread (&jugadores[i].p_ganadas, sizeof(int), 1, fichero);
        fread (&jugadores[i].p_perdidas, sizeof(int), 1, fichero);
        extra_info[i].p_totales = jugadores[i].p_ganadas + jugadores[i].p_perdidas;
        extra_info[i].win_rate = (((float)jugadores[i].p_ganadas /(float) extra_info[i].p_totales) * 100);
        aux_nombre[0] = '\0';

        }

        opcion_orden = RANKING_elegirOrden();
        //ESTE SWITCH LO METERIA EN UNA FUNCION APARTE FUNCION DEMASIADO GRANDE
        switch (opcion_orden) {
          case 1:

            RANKING_ordenarAlfabetico(jugadores,extra_info, num_jugadores);

            RANKING_printarDatos (jugadores, extra_info, num_jugadores);

            break;
          case 2:

            RANKING_ordenWinRate (jugadores, extra_info, num_jugadores);

            RANKING_printarDatos (jugadores, extra_info, num_jugadores);

            break;
          default:
            printf("%s\n", MENSAJE_ERROR_OPCION);
            break;
      }
    }
  }
}
