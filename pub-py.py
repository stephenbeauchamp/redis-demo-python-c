#!/usr/bin/python

import redis
import time

sensa_data_queue_name = 'SENSA_DATA_QUEUE'

que = redis.Redis()

i=0

while i < 60:
    i += 1
    msg = 'pub by pub-py {}'.format( i )
    que.lpush( sensa_data_queue_name, msg )
    print( 'INFO: ' + msg )
    time.sleep( 0.500 )
