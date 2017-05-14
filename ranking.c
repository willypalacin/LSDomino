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
