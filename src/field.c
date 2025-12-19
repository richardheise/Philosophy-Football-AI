#include <stdlib.h>
#include <string.h>
#include <hiredis/hiredis.h>
#include "field.h"

redisContext *redis_context;
redisReply *redis_reply;
char field_side;
char key[16];

void field_connect(int argc, char **argv) {
  char *ip;
  int port;

  if(argc < 2) {
    printf("format: %s side ip port\n", argv[0]);
    printf("   side: indicates the side of the field, possible values are e or d\n");
    printf("   ip: optional parameter that indicates the ip or hostname of the redis server\n");
    printf("       the default value is 127.0.0.1\n");
    printf("   port: optional parameter that indicates the redis server port\n");
    printf("          the default value is 10001\n");
    exit(1);
  }

  field_side = argv[1][0];
  ip  = (argc > 2) ? argv[2] : "127.0.0.1";
  port = (argc > 3) ? atoi(argv[3]) : 10001;

  redis_context = redisConnect(ip, port);

  if (redis_context == NULL || redis_context->err) {
    if(redis_context) {
      printf("Error connecting to redis server: %s\n", redis_context->errstr);
      exit(1);
    } else {
      printf("Could not connect to redis server\n");
    }
  }
}

void field_send(char *buffer) {
  sprintf(key, "mov_%c", field_side);
  redis_reply = redisCommand(redis_context, "RPUSH %s %s", key, buffer);
  freeReplyObject(redis_reply);
}

void field_receive(char *buffer) {
  sprintf(key, "field_%c", field_side);
  redis_reply = redisCommand(redis_context, "BLPOP %s 0", key);
  strcpy(buffer, redis_reply->element[1]->str);
  freeReplyObject(redis_reply);
}
