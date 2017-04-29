#include "menu.h"



void MENU_mostrarMenu() {
  printf("%s\n", MENU_WELCOME);
  printf("\t%s\n", MENU_OP1);
  printf("\t%s\n", MENU_OP2);
  printf("\t%s\n", MENU_OP3);
  printf("%s", "Opcion: ");


}

void MENU_seleccionarOpcion (int opcion) {
  Player * players;
  int num_players;
  switch (opcion) {
    case 1:

    JUGADORES_leerFichero(&players, &num_players);
    //printf("%s\n", OPCION_INHABILITADA);
      //Meter nueva partida
      break;
    case 2:
      //opcion_orden = elegirOrden ();
      RANKING_abrirFichero();
      /*switch (opcion_orden) {
        case 1:
          ordenAlfabetico ();
          mostrarRanking ();
          break;
        case 2:
          ordenWinRate ();
          mostrarRanking ();
          break;
        default:
        printf("%s\n", MENSAJE_ERROR_OPCION);
        break;
      }*/
      break;
    case 3:
      printf("%s\n", "Gracias por usar nuestros servicios");
      break;
    default:
      printf("%s\n", MENSAJE_ERROR_OPCION);
      break;
  }



}
