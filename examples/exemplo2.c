#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "field.h"

#define MAX_STR 512

int main(int argc, char **argv) {
  char buf[MAX_STR];
  char *line;

  field_connect(argc, argv);

  while(1) {
    field_receive(buf);
    printf("%s", buf);
    line = readline(NULL);
    if(line[0] == '0')
      break;
    sprintf(buf, "%s\n", line);
    free(line);
    field_send(buf);
  }
}
