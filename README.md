# redis PUB/SUB examples in Python and C

This is a demo that uses a Redis pub/Sub LIFO queue to allow inter app communication.

The apps (either publisher and/or subscriber) are written in Python and C. Any combination
of publisher and subscriber should work.

## pre-requisites
This demo is designed to run on a Raspberry PI with the following installed:
```
$ sudo apt install -y redis-server python-redis
$ sudo apt install -y libhiredis-dev
```

## pub-py.py
This is a python script to publish messages.
```
$ python pub-py.py
```

## pub-c.c
This is a C application to publish messages. Compile it and run it with these commands (it will publish 60 messages):
```
$ gcc -I /usr/include/hiredis/ -l hiredis -o pub-c pub-c.c
$ ./pub-c
```

## sub-py.py
This is a python script to subscribe to messages. Run it with this command (Ctrl+c to quit):
```
$ python sub-py.py
```


## pub-c.c
This is a C application to subscribe to messages. Compile it and run it with these commands (Ctrl+c to quit):
```
$ gcc -I /usr/include/hiredis/ -l hiredis -o pub-c pub-c.c
$ ./pub-c
```

## Scenarios
Open 5 ssh sessions. Run each of the scripts/app above in each and a redis monitor in the 5th:
$ redis-cli monitor
