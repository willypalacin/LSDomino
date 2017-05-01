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
  ListaPDI l;
  int num_players;
  int i,j;
  switch (opcion) {
    case 1:

      JUGADORES_leerFichero(&players, &num_players);
      //Hasta aquí ya tenemos la estructura de jugadores, faltará ordenarla segun el orden de tirada


      JUGADORES_ordenSegunTurno(&players, num_players);


      l = LISTAPDI_crea();
      LOGICA_generarFichas(&l);

    //LISTAPDI_irInicio(&l);
    //Borrar esto
    
    /*
    printf("\n\n");
    LOGICA_fichasRandom(&l);

    for(i = 0; i <= 6; i++) {
      printf("\n");
      for (j = i; j <= 6; j++) {
        f = LISTAPDI_consultar(l);
        printf("[%d|%d] ", f.cara1, f.cara2);

        LISTAPDI_avanzar (&l);

      }



    }*/
      printf("\n\n");


        //printf("%s\n", OPCION_INHABILITADA);

      break;
    case 2:
      //opcion_orden = elegirOrden ();
      RANKING_abrirFichero();

      break;
    case 3:
      printf("%s\n", "Gracias por usar nuestros servicios");
      break;
    default:
      printf("%s\n", MENSAJE_ERROR_OPCION);
      break;
  }



}
