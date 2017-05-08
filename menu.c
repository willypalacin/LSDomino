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
  ListaPDI * lista_jugadores;
  int num_players;
  int i,j;
  int fin = 0;
  switch (opcion) {
    case 1:

      JUGADORES_leerFichero(&players, &num_players);
      //Hasta aquí ya tenemos la estructura de jugadores, faltará ordenarla segun el orden de tirad
      JUGADORES_ordenSegunTurno(&players, num_players);

      l = LISTAPDI_crea();
      LOGICA_generarFichas(&l);

      //LOGICA_pintarTablero(&l);

      lista_jugadores = (ListaPDI *) malloc (sizeof(ListaPDI) * num_players);
      if(lista_jugadores == NULL) {
        printf("%s\n",ERROR_ESTRUCTURA_JUGADORES);
      }
      else {
        for(i = 0; i < num_players; i++) {
          lista_jugadores[i] = LISTAPDI_crea();
          for(j = 0; j < 5; j++){
            LOGICA_robarFicha(&l, lista_jugadores, i);
          }
        }
      }

      //Aqui comienza el JUEGO
      LOGICA_dinamicaJuego(&l, lista_jugadores, players ,num_players);



      break;
    case 2:
      //opcion_orden = elegirOrden ();
      RANKING_abrirFichero();

      break;
    case 3:
      printf("%s\n", MENSAJE_ADIOS);
      break;
    default:
      printf("%s\n", MENSAJE_ERROR_OPCION);
      break;
  }



}
