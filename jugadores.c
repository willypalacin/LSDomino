#include "jugadores.h"


void JUGADORES_leerFichero(Player* *players, int * num_players, char ** argv) {

  FILE * f_players;
  f_players = fopen(argv[2],"r");
  if (f_players == NULL) {
    printf("%s\n", ERROR_FICHERO_JUGADORES);

  }
  else {
    fscanf(f_players,"%d", num_players);
    JUGADORES_guardarEnEstructura(f_players, players, *num_players);
  }

}

int JUGADORES_extraerDatos(char aux[100]) {
  int num_caracteres, i;
  i = 0;
  num_caracteres = 0;
  while (aux[i] != '/') {
    num_caracteres++;
    i++;

  }
  return num_caracteres;


}

int JUGADORES_comprobarFicheroPlayers(char* *argv) {
  int num_players, num_caracteres, i;
  FILE * f;
  int error = 0;
  num_caracteres = 0;
  char aux[100];
  f = fopen(argv[2], "r");
  fscanf(f,"%d",&num_players);
  if(num_players != 2 && num_players != 3 && num_players != 4) {
    printf("%s\n", ERROR_NUMERO_DE_JUGADORES);
    error = 1;

  }
  else {
    i = 0;
    fgets(aux, 100, f);
    while (i < num_players) {
      fgets(aux, 100, f);
      num_caracteres = JUGADORES_extraerDatos(aux);
      if(num_caracteres > 20) {
        printf(ERROR_CARACTERES, i+1);
        error = 1;
      }
      num_caracteres = 0;
      aux[0] = '\0';
      i++;
    }

  }
  fclose(f);
  return error;
}


void JUGADORES_asignarCadena(Player ** players, char cadena[20], int w) {

  int u = 0;
  int i = 0;
  while(cadena[i]!= '/') {
    i++;

  }
  (*players)[w].nombre = (char *) malloc((i+1)* sizeof(char));
  if((*players)[w].nombre == NULL) {
    printf("%s\n", ERROR_MEMORIA );

  }
  else {
    while(u < i) {
      (*players)[w].nombre[u] = cadena[u];
      u++;
    }
    (*players)[w].turno = (cadena[u+1] - '0');
  }
  cadena[0] = '\0';
}

void JUGADORES_guardarEnEstructura (FILE * f_players, Player ** players, int  num_players) {
  int i = 0;
  char cadena[20];

  *players = (Player *) malloc (sizeof(Player) * num_players);

  if (*players == NULL) {
    printf("%s\n", ERROR_MEMORIA );
  }
  else {
    //no hace falta prelectura, sabemos el num de jugadores
    i = 0;
    //almacenamos en un gets que luego trataremos por separado en asignar cadena
    fgets(cadena, 20 , f_players);

    while (i<num_players) {
      fgets(cadena, 20 , f_players);
      JUGADORES_asignarCadena(players ,cadena, i);

      i++;
    }
  }
  fclose(f_players);
}

void JUGADORES_ordenSegunTurno(Player ** players, int n) {
  //bubble sort que ordena segun el turno correspondiente
  Player tmp_player;
  int i, j;
  for (i = 0 ; i < ( n - 1 ); i++) {
      for (j = 0 ; j < n - i - 1; j++) {
        if ((*players)[j].turno > (*players)[j+1].turno) {
          tmp_player = (*players)[j];
          (*players)[j] = (*players)[j+1];
          (*players)[j+1] = tmp_player;

        }
      }
    }
  }
