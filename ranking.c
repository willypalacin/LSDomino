#include "ranking.h"


void abrirFichero () {
  FILE * fichero;
  int num_jugadores;

  fichero = fopen ("ranking.bin", "rb");
  if (fichero == NULL){
    fflush(stdout);
    printf ("%s\n", ERROR_FICHERO);
  }
  else{
    fread (&num_jugadores, sizeof(int), 1, fichero);
    crearEstructura (fichero, num_jugadores);
    fclose (fichero);
  }
}

void printarDatos (Jugador j, Extra_info extra){
  printf("\n");
  printf ("Jugador: %s\n", j.nombre);
  printf ("P.Ganadas: %d\n", j.p_ganadas);
  printf ("P.Perdidas: %d\n", j.p_perdidas);
  printf ("P.Totales: %d\n", extra.p_totales);
  printf ("Win Rate: %.2f%%\n", extra.win_rate);
  printf("\n");

}

int elegirOrden() {
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

void ordenWinRate (Jugador * jugadores, Extra_info * extra_info ,int num_jugadores) {
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
  for (i = 0; i < num_jugadores; i++) {
    printarDatos (jugadores[i], extra_info[i]);
  }

}

void crearEstructura (FILE * fichero, int num_jugadores){
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
        opcion_orden = elegirOrden ();
        switch (opcion_orden) {
          case 1:
          printf("%s\n", OPCION_INHABILITADA);
            //ordenAlfabetico (extra_info, jugadores, num_jugadores);
            break;
          case 2:
            ordenWinRate (jugadores, extra_info, num_jugadores);
            break;
          default:
          printf("%s\n", MENSAJE_ERROR_OPCION);
          break;
      }
    }
  }
}
