//
// COMPILE WITH:
//   $ gcc -I /usr/include/hiredis/ -l hiredis -o pub-c pub-c.c
// RUN WITH
//   $ ./pub-c
//

#include <stdio.h>
#include <stdlib.h>
#include <hiredis.h>
#include <time.h>
#include <unistd.h>

int main( int argc, char **argv ) {
  //
  redisContext *redis_conn;
  redisReply *reply = NULL;
  const char *redis_host = "127.0.0.1";
  int redis_port = 6379;
  struct timeval redis_timeout = { 1, 500000 }; // 1.5 Seconds
  //
  redis_conn = redisConnectWithTimeout( redis_host, redis_port, redis_timeout );
  if ( redis_conn == NULL || redis_conn->err ) {
    printf( "ERROR: could not open connection with redis...\n" );
    exit ( 1 );
  }

  char *sensa_data_queue_name = "SENSA_DATA_QUEUE";

  int i = 0;

  while( i++<60 ) {
    char msg[64];
    snprintf( msg, 64, "pub by pub-c %d", i );
    // WEIRD, YOU MUST USE %s TO PUSH THE DATA AS A STRING. IF YOU JUST PASS A PRE_PREPARED
    // STRING buf, IT BREAKS UP THE DATA INTO SEPARATE MESSAGES AT EVERY SPACE.
    reply = redisCommand( redis_conn, "LPUSH %s %s", sensa_data_queue_name, msg );
    printf( "INFO: LPUSH %s %s\n", sensa_data_queue_name, msg );
    freeReplyObject( reply );
    usleep( 500 * 1000 ); // microseconds * 1000 = milliseconds
  }

  redisFree( redis_conn );

  return 0;
}
