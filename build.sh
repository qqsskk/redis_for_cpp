echo build_redis
g++ -g -c redis_handler.h redis_handler.cpp

echo build_main
g++ -g -c main.cpp

echo link
g++ -g redis_handler.o main.o -o test -lhiredis -levent
