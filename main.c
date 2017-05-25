#include <stdio.h>
#include "menu.h"
#include <conio.h>
#include <string.h>

#define ERROR_ARGC "Error, el formato introducido es incorrecto. Debe anadir los dos ficheros, primero el binario y despues el de jugadores."
#define CREAR_RANKING "No existe el fichero Ranking... Creando ranking.bin"
#define ERROR_NOMBRE_FICHERO_PLAYERS "Error al abrir el fichero de jugadores. Vigile que este correctamente importado"




int main (int argc, char* *argv) {
  FILE * f;
  int opcion;


  if (argc != 3) {
    printf("%s\n", ERROR_ARGC );

  }
  else {
    f = fopen(argv[1], "r");
    if(fopen(argv[2], "r") == NULL) {
      printf("%s\n", ERROR_NOMBRE_FICHERO_PLAYERS);


    }
    else {
      if (f == NULL) {
        printf("%s\n", CREAR_RANKING );
        f = fopen("ranking.bin", "wb");

      }
      fclose(f);
      do {
        MENU_mostrarMenu();
        fflushnou();
        scanf("%d",&opcion);

        MENU_seleccionarOpcion(opcion);
      } while (opcion != 3);
    }
  }

  //crearFichero();



return 0;
}
