//
// COMPILE WITH:
//   $ gcc -I /usr/include/hiredis/ -l hiredis -o sub-c sub-c.c
// RUN WITH
//   $ ./sub-c
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

  while( 1 ) {
    reply = redisCommand( redis_conn, "BLPOP %s %d", sensa_data_queue_name, 0 );
    printf( "INFO: sending command: BLPOP %s %d\n", sensa_data_queue_name, 0 );
    if ( !reply ) {
      printf( "WARN: queue blpop reply is a null object...\n" );
    } else if ( redis_conn->err ) {
      printf( "WARN: queue blpop reply causes context error: \n" );
    } else {
      switch ( reply->type ) {
        case REDIS_REPLY_ERROR:
          printf( "INFO: queue blpop reply is a error: %s\n", reply->str );
          break;
        case REDIS_REPLY_INTEGER:
          printf( "INFO: queue blpop reply is an integer: %lld\n", reply->integer );
          break;
        case REDIS_REPLY_NIL:
          printf( "INFO: queue blpop reply is NIL ...\n" );
          break;
        case REDIS_REPLY_STRING:
          printf( "INFO: queue blpop reply is a string: %s\n", reply->str );
          break;
        case REDIS_REPLY_ARRAY:
          printf( "INFO: queue blpop reply is an array...\n" );
          for( int repIdx=0; repIdx<reply->elements; repIdx++ ){
            printf( "INFO:   reply[%d] %s\n", repIdx, reply->element[repIdx]->str );
          }
          break;
        default:
          printf( "WARN: queue blpop reply unknown reply type %d\n", reply->type );
          break;
      }
      freeReplyObject( reply );
    }
    usleep( 10 * 1000 ); // microseconds * 1000 = milliseconds
  }

  redisFree( redis_conn );

  return 0;
}
