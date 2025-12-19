
/**
 * Autores:
 * Richard Fernando Heise Ferreira GRR20101053
 * Carlos Iago Bueno GRR20190171
 */
#include "marIA_lib.h"
#include "field.h"

// Main da nossa IA
int main(int argc, char **argv) {
  char *buffer = create_string();
  char *line;

  field_connect(argc, argv);

  while(1) {
    field_receive(buffer);
    // chama o resolutor
    line = solve(buffer);

    if(line[0] == '0')
        break;

    sprintf(buffer, "%s\n", line);
    free(line);
    field_send(buffer);
  }

  free(buffer);
}