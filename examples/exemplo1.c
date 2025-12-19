#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "field.h"

#define MAX_STR 512
#define MAX_INT 16

int main(int argc, char **argv) {
  char buf[MAX_STR];
  char field[MAX_STR];
  char my_side;
  char opponent_side;
  char opponent_move;
  int field_size;
  int philosopher_pos;
  int ball_pos[MAX_INT];
  int num_jumps;
  int i;

  // conecta com o controlador do campo
  field_connect(argc, argv);

  // recebe o campo inicial e o movimento do adversario
  field_receive(buf);

  // separa os elementos do string recebido
  sscanf(strtok(buf, " \n"), "%c", &my_side);
  sscanf(strtok(NULL, " \n"), "%d", &field_size);
  sscanf(strtok(NULL, " \n"), "%s", field);
  sscanf(strtok(NULL, " \n"), "%c", &opponent_side);
  sscanf(strtok(NULL, " \n"), "%c", &opponent_move);
  if(opponent_move != 'n') {
    if(opponent_move == 'f')
      sscanf(strtok(NULL, " \n"), "%d", &philosopher_pos);
    else {
      sscanf(strtok(NULL, " \n"), "%d", &num_jumps);
      for(i = 0; i < num_jumps; i++)
	sscanf(strtok(NULL, " \n"), "%d", &(ball_pos[i]));
    }
  }

  // mostra o que recebeu
  printf("%c %d %s\n", my_side, field_size, field);
  printf("%c %c", opponent_side, opponent_move);
  if(opponent_move != 'n') {
    if(opponent_move == 'f')
      printf(" %d", philosopher_pos);
    else {
      printf(" %d", num_jumps);
      for(i = 0; i < num_jumps; i++)
	printf(" %d", ball_pos[i]);
    }
  }
  printf("\n");

  // prepara um string com o movimento
  // de inserir um filosofo na posicao 1 do campo
  sprintf(buf, "%c f %d\n", my_side, 1);

  // envia o movimento para o controlador do campo
  field_send(buf);
}
