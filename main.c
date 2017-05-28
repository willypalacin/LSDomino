#include <stdio.h>
#include "menu.h"
#include <conio.h>
#include <string.h>

#define ERROR_ARGC "Error, el formato introducido es incorrecto. Debe anadir los dos ficheros, primero el binario y despues el de jugadores."
#define CREAR_RANKING "No existe el fichero Ranking... Creando el fichero"
#define ERROR_NOMBRE_FICHERO_PLAYERS "Error al abrir el fichero de jugadores. Vigile que este correctamente importado"


int main (int argc, char* *argv) {
  FILE * f;
  int opcion;
  int error_players = 0;

  if (argc != 3) {
    printf("%s\n", ERROR_ARGC );
  }
  else {
    if(fopen(argv[2], "r") == NULL) {
      printf("%s\n", ERROR_NOMBRE_FICHERO_PLAYERS);

    }
    else {
      error_players = JUGADORES_comprobarFicheroPlayers(argv);
      if(error_players != 1){
        f = fopen(argv[1], "rb");
        if (f == NULL) {
          printf("%s\n", CREAR_RANKING );
          f = fopen(argv[1], "wb");

        }
        fclose(f);
        do {
          MENU_mostrarMenu();
          fflushnou();
          scanf("%d",&opcion);

          MENU_seleccionarOpcion(opcion, argv);
        } while (opcion != 3);
      }
    }
  }
  return 0;
}
