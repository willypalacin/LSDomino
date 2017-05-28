#include "menu.h"



void MENU_mostrarMenu() {

  printf("%s\n", MENU_WELCOME);
  printf("\t%s\n", MENU_OP1);
  printf("\t%s\n", MENU_OP2);
  printf("\t%s\n", MENU_OP3);
  printf("%s", "Opcion: ");

}



void MENU_seleccionarOpcion (int opcion, char * *argv) {

  Player * players;
  ListaPDI l;
  ListaPDI * lista_jugadores;
  Jugador * jugadores;
  int num_jugs_ranking;
  ListaPDI tablero;
  int num_players;
  int i,j;
  
  num_jugs_ranking = 0;

  RANKING_numJugadoresIniciales(&num_jugs_ranking, argv);


  if(num_jugs_ranking != 0) {
    RANKING_almacenoJugadores(&jugadores, num_jugs_ranking, argv);
  }
  switch (opcion) {
    case 1:

      JUGADORES_leerFichero(&players, &num_players, argv);
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
      tablero = LISTAPDI_crea();
      LISTAPDI_inserir(&tablero, LISTAPDI_consultar(l));
      LISTAPDI_borrar(&l);
      //Aqui comienza el JUEGO
      LOGICA_dinamicaJuego(&l, lista_jugadores, &tablero, players ,num_players, jugadores, num_jugs_ranking, argv);

      break;

    case 2:
      //opcion_orden = elegirOrden ();
      RANKING_abrirFichero(argv);

      break;
    case 3:
      printf("%s\n", MENSAJE_ADIOS);
      break;
    default:
      printf("%s\n", MENSAJE_ERROR_OPCION);
      break;
  }



}
