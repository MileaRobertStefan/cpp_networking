rm -rf ./obj
mkdir ./obj

# g++ ./client/main.cpp -o ./obj/client_main.o
g++ ./server/main_server.cpp -pthread -o ./obj/main_server.o
g++ ./client/main_client.cpp -o ./obj/main_client.o

./obj/main_server.o