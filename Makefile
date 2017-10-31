OBJ=pixku.o ugen.o main.o circbuf.o pulse.o orbit.o

CFLAGS=-I$(HOME)/.runt/include -fPIC -Wall -ansi -g
LDFLAGS= -L$(HOME)/.runt/lib/ -lrunt -ldl -lrunt_img -lGL -lrunt_cray -lm

LDFLAGS += -lrunt_cairo -lcairo
LDFLAGS += -lrunt_plumber
LDFLAGS += -lrunt_scheme
LDFLAGS += -lrunt_patchwerk
LDFLAGS += -lrunt_math
LDFLAGS += -lrunt_ll

LDFLAGS += -lspigot -lglfw -lsqlite3
LDFLAGS += -lstdc++

LDFLAGS +=-lsporth -lsoundpipe -lm -ljack -ldl -lpthread -lsndfile

default: all

all: pixku 

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

pixku: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

install: pixku
	mkdir -p $(HOME)/.runt/bin
	install pixku $(HOME)/.runt/bin

clean: 
	rm -rf pixku $(OBJ)
	rm -rf pixku.so
