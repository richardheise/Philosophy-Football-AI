#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hiredis/hiredis.h>

#define MAX_STR 512
#define MAX_INT 16
#define OTHER(l) (l=='d'?'e':'d')

redisContext* init(int argc, char **argv, char *side, int *size,
		     int *plays, char *time) {
  redisContext *redis_context;
  char *ip;
  int port;

  if(argc < 5) {
    printf("format:\n");
    printf("         %s side size plays time [ip port]\n\n", argv[0]);
    printf("   side: starting side of the field, possible values are e or d\n");
    printf("   size: size of the field, must be odd\n");
    printf("   plays: maximum number of plays in the match\n");
    printf("   time: time limit in seconds for each play, 0 means no limit\n");
    printf("   ip: optional parameter that indicates the ip or hostname of the redis server\n");
    printf("       the default value is 127.0.0.1\n");
    printf("   port: optional parameter that indicates the redis server port\n");
    printf("          the default value is 10001\n");
    exit(1);
  }

  *side = argv[1][0];
  *size = atoi(argv[2]);
  *plays = atoi(argv[3]);
  strcpy(time, argv[4]);
  ip  = (argc > 5) ? argv[5] : "127.0.0.1";
  port = (argc > 6) ? atoi(argv[6]) : 10001;

  redis_context = redisConnect(ip, port);
  if (redis_context == NULL || redis_context->err) {
    if(redis_context) {
      printf("Error connecting to redis server: %s\n", redis_context->errstr);
      exit(1);
    } else {
      printf("Could not connect to redis server\n");
    }
  }
  return redis_context;
}

int parse_mov(char *buf, char *rl, char *rm, int *rf, int *rs, int *rb) {
  int i;
  char *s;

  if(!(s = strtok(buf, " \n")) || sscanf(s , "%c", rl) != 1)
    return 0;
  if(*rl != 'e' && *rl != 'd')
    return 0;
  if(!(s = strtok(NULL, " \n")) || sscanf(s, "%c", rm) != 1)
    return 0;
  if(*rm != 'n' && *rm != 'f' && *rm != 'o')
    return 0;
  if(*rm != 'n') {
    if(*rm == 'f') {
      if(!(s = strtok(NULL, " \n")) || sscanf(s, "%d", rf) != 1)
	return 0;
    }
    else {
      if(!(s = strtok(NULL, " \n")) || sscanf(s, "%d", rs) != 1)
	return 0;
      for(i = 0; i < *rs; i++)
	if(!(s = strtok(NULL, " \n")) || sscanf(s, "%d", &(rb[i])) != 1)
	  return 0;
    }
  }
  return 1;
}

int apply_mov(char *buf, char *field, int size,
	       char rl, char rm, int rf, int rs, int *rb) {
  int i, j, inc, ball;

  strcpy(buf, field);
  if(rm == 'n')
    return 1;
  if(rm == 'f') {
    if(--rf < 0 || rf >= size)
      return 0;
    if(buf[rf] == '.') {
      buf[rf] = 'f';
      return 1;
    }
    return 0;
  }
  if(rm == 'o') {
    if(rs < 1)
      return 0;
    for(ball = 0; ball < size; ball++)
      if(buf[ball] == 'o')
	break;
    for(i = 0; i < rs; i++) {
      if(ball < 0 || ball >= size)
	break;
      inc = (--rb[i] < ball) ? -1 : 1;
      j = ball + inc;
      if(j == rb[i])
	return 0;
      for(; j != rb[i]; j += inc)
	if(buf[j] != 'f')
	  return 0;
        else
	  buf[j] = '.';
      buf[ball] = '.';
      ball = rb[i];
      if(ball >= 0 && ball < size) {
	if(buf[ball] == '.')
	  buf[ball] = 'o';
	else
	  return 0;
      }
      if(ball < 0 && rl == 'e')
	return 0;
      if(ball >= size && rl == 'd')
	return 0;
    }
    if(i == rs)
      return 1;
  }
  return 0;
}

int goal(char *field, int size) {
  int i;

  for(i = 0; i < size; i++)
    if(field[i] == 'o')
      return 0;
  return 1;
}

void clear_field(char *field, int size) {
  int i;

  for(i = 0; i < size; i++)
    field[i] = '.';
  field[size] = 0;
}

int main(int argc, char **argv) {
  redisContext *c;
  redisReply *r;
  char buf[MAX_STR];
  char field[MAX_STR];
  char mov[MAX_STR];
  char key[16];
  char timeout[16];
  char side;
  char winner;
  char rl;
  char rm;
  int rf;
  int rs;
  int rb[MAX_INT];
  int plays;
  int size;
  int ok;

  c = init(argc, argv, &side, &size, &plays, timeout);

  winner = ' ';
  clear_field(field, size);
  field[size/2] = 'o';

  printf("%d: %s\n", plays, field);

  sprintf(buf, "%c %d %s\n%c n\n", side, size, field, OTHER(side));

  while(plays) {
    sprintf(key, "field_%c", side);
    r = redisCommand(c, "LTRIM %s 1 0", key);
    freeReplyObject(r);
    r = redisCommand(c, "RPUSH %s %s", key, buf);
    freeReplyObject(r);

    ok = 0;
    sprintf(key, "mov_%c", side);
    r = redisCommand(c, "BLPOP %s %s", key, timeout);
    if(r->type != REDIS_REPLY_NIL) {
      strcpy(mov, r->element[1]->str);
      if(parse_mov(mov, &rl, &rm, &rf, &rs, rb) &&
	 apply_mov(buf, field, size, rl, rm, rf, rs, rb)) {
	  strcpy(field, buf);
	  strcpy(mov, r->element[1]->str);
	  ok = 1;
	}
    }
    freeReplyObject(r);
    if(!ok)
      sprintf(mov, "%c n\n", side);

    printf("%d: %s", plays, mov);
    printf("%d: %s\n", plays, field);

    if(goal(field, size)) {
      printf("%d: goal by %c\n", plays, side);
      winner = side;
      break;
    }

    side = OTHER(side);
    sprintf(buf, "%c %d %s\n%s", side, size, field, mov);
    plays--;
  }

  clear_field(field, size);

  sprintf(buf, "e %d %s\nd n\n", size, field);
  r = redisCommand(c, "RPUSH field_e %s", buf);
  freeReplyObject(r);

  sprintf(buf, "d %d %s\ne n\n", size, field);
  r = redisCommand(c, "RPUSH field_d %s", buf);
  freeReplyObject(r);

  if(plays == 0)
    printf("draw\n");
  else
    printf("winner: %c\n", winner);
}
