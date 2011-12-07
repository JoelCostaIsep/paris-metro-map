#C_FLAGS = -Wall -g -std=c99
C_FLAGS = -Wall -g
LD_FLAGS = -lm
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
CC = gcc

all : test_sta test_ligne test_connexion test_dijkstra metro_v0 metro_v1 metro_v2 #metro_v3

depend : $(SRC)
	$(CC) -MM $^ > .depend

-include .depend

%.o: %.c
	$(CC) $(C_FLAGS) -c $<

metro_callback_v0.o : metro_callback_v0.c
	gcc ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_callback_v0.c

metro_v0.o : metro_v0.c
	gcc ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_v0.c

metro_callback_v1.o : metro_callback_v1.c
	gcc ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_callback_v1.c

metro_v1.o : metro_v1.c
	gcc ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_v1.c

metro_callback_v2.o : metro_callback_v2.c
	gcc ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_callback_v2.c

metro_v2.o : metro_v2.c
	gcc ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_v2.c

metro_callback_v3.o : metro_callback_v3.c
	gcc ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_callback_v3.c

metro_v3.o : metro_v3.c
	gcc ${C_FLAGS} `pkg-config --cflags gtk+-2.0` -c metro_v3.c


test_sta : depend test_sta.o liste.o truc.o abr.o ligne.o
	$(CC) $(C_FLAGS) -o test_sta test_sta.o truc.o liste.o abr.o ligne.o $(LD_FLAGS)

test_ligne : depend test_ligne.o ligne.o
	$(CC) $(C_FLAGS) -o test_ligne test_ligne.o ligne.o

test_connexion : depend test_connexion.o ligne.o abr.o liste.o truc.o
	$(CC) $(C_FLAGS) -o test_connexion test_connexion.o ligne.o abr.o liste.o truc.o $(LD_FLAGS)

test_dijkstra : depend test_dijkstra.o ligne.o abr.o liste.o truc.o dijkstra.o
	$(CC) $(C_FLAGS) -o test_dijkstra test_dijkstra.o ligne.o abr.o liste.o truc.o dijkstra.o $(LD_FLAGS)

metro_v0 : metro_v0.o metro_callback_v0.o liste.o truc.o depend
	gcc ${C_FLAGS} `pkg-config --libs gtk+-2.0` -o metro_v0 metro_v0.o metro_callback_v0.o liste.o truc.o ligne.o abr.o 

metro_v1 : metro_v1.o metro_callback_v1.o liste.o truc.o ligne.o abr.o depend
	gcc ${C_FLAGS} `pkg-config --libs gtk+-2.0` -o metro_v1 metro_v1.o metro_callback_v1.o liste.o truc.o ligne.o abr.o

metro_v2 : metro_v2.o metro_callback_v2.o liste.o truc.o ligne.o abr.o aqrtopo.o depend
	gcc ${C_FLAGS} `pkg-config --libs gtk+-2.0` -o metro_v2 metro_v2.o metro_callback_v2.o liste.o truc.o ligne.o abr.o aqrtopo.o 

metro_v3 : metro_v3.o metro_callback_v3.o liste.o truc.o ligne.o abr.o aqrtopo.o depend
	gcc ${C_FLAGS} `pkg-config --libs gtk+-2.0` -o metro_v2 metro_v2.o metro_callback_v3.o liste.o truc.o ligne.o abr.o aqrtopo.o 

clean :
	rm -f $(OBJ) test_sta test_ligne test_connexion test_dijkstra .depend metro_v0 metro_v1 metro_v2 metro_v3

.PHONY: all clean depend