OBJ=pixku.o ugen.o main.o

CFLAGS=-I$(HOME)/.runt/include -fPIC -Wall -ansi -g
LDFLAGS= -L$(HOME)/.runt/lib/ -lrunt -ldl -lrunt_img -lGL -lrunt_cray -lm
LDFLAGS += -lrunt_cairo -lcairo

LDFLAGS +=-lsporth -lsoundpipe -lm -ljack -ldl -lpthread -lsndfile

default: all

all: pixku 

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

pixku: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

clean: 
	rm -rf pixku $(OBJ)
	rm -rf pixku.so
