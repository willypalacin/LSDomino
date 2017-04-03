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

      for (i = 0; i < num_jugadores; i++){
        fread (&jugadores[i], sizeof(Jugador), 1, fichero);
        extra_info[i].p_totales = jugadores[i].p_ganadas + jugadores[i].p_perdidas;
        extra_info[i].win_rate = (((float)jugadores[i].p_ganadas /(float) extra_info[i].p_totales) * 100);
        printarDatos (jugadores[i], extra_info[i]);

      }
    }
  }
}
      /*opcion_orden = elegirOrden ();
      switch (opcion_orden) {
        case 1:
          //ordenAlfabetico (extra_info, jugadores, num_jugadores);
          break;
        case 2:
          //ordenWinRate (extra_info, jugadores, num_jugadores);
          break;
        default:
        printf("%s\n", MENSAJE_ERROR_OPCION);
        break;


      }
    }
  }
}

int elegirOrden () {
  int opcion_orden;
  do {
    printf("%s\n", MOSTRAR_POSIBILIDADES);
    printf("\t%s\n", ORDEN_ALFABETICO);
    printf("\t%s\n", ORDEN_WIN_RATE);
    printf("%s\n", "Opcion para ordenar [1/2]: ");
    scanf ("%d", &opcion_orden);

  } while (opcion_orden != 1 || opcion_orden != 2);

  return opcion_orden;
}


*/

void printarDatos (Jugador j, Extra_info extra){
  printf("\n");
  printf ("Jugador: %s\n", j.nombre);
  printf ("P.Ganadas: %d\n", j.p_ganadas);
  printf ("P.Perdidas: %d\n", j.p_perdidas);
  printf ("P.Totales: %d\n", extra.p_totales);
  printf ("Win Rate: %.2f%%\n", extra.win_rate);
  printf("\n");

}
