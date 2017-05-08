#include "jugadores.h"


void JUGADORES_leerFichero(Player* *players, int * num_players) {

  FILE * f_players;
  f_players = fopen("player.txt","r");
  if (f_players == NULL) {
    printf("%s\n", ERROR_FICHERO_JUGADORES);

  }
  else {
    fscanf(f_players,"%d", num_players);
    JUGADORES_guardarEnEstructura(f_players, players, *num_players);
  }

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
  cadena = " ";
}

void JUGADORES_guardarEnEstructura (FILE * f_players, Player ** players, int  num_players) {
  int i = 0;
  char cadena[20];

  *players = (Player *) malloc (sizeof(Player) * num_players);

  if (*players == NULL) {
    printf("%s\n", ERROR_MEMORIA );
  }
  else {
    i = 0;
    fgets(cadena, 20 , f_players);
    while (i<num_players) {
      fgets(cadena, 20 , f_players);
      JUGADORES_asignarCadena(players ,cadena, i);
      i++;
    }
  }
}

void JUGADORES_ordenSegunTurno(Player ** players, int n) {
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
