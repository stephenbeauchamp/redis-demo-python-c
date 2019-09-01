import redis

sensa_data_queue_name = 'SENSA_DATA_QUEUE'

que = redis.Redis()

while True:
    msg = que.blpop( sensa_data_queue_name )
    print( 'INFO: sub-py received from the que: {}'.format( msg ) )
