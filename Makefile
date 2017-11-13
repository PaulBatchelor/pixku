.PHONY: osx linux

OBJ=pixku.o ugen.o main.o circbuf.o pulse.o orbit.o

CFLAGS=-I$(HOME)/.runt/include -fPIC -Wall -g
LDFLAGS= -L$(HOME)/.runt/lib/ -lrunt -ldl -lrunt_img -lrunt_cray -lm

LDFLAGS += -lrunt_cairo -lcairo
LDFLAGS += -lrunt_plumber
LDFLAGS += -lrunt_scheme
LDFLAGS += -lrunt_patchwerk
LDFLAGS += -lrunt_math
LDFLAGS += -lrunt_ll

LDFLAGS += -lspigot -lglfw -lsqlite3
LDFLAGS += -lstdc++

LDFLAGS +=-lsporth -lsoundpipe -lm -ldl -lpthread -lsndfile

default: ; @echo "Usage: make [linux|osx]"

osx: ; make -f Makefile -f Makefile.osx all

linux: ; make -f Makefile -f Makefile.linux all

all: pixku 

%.o: %.c
	$(CC) -ansi $(CFLAGS) $< -c -o $@

pixku: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

install: pixku
	mkdir -p $(HOME)/.runt/bin
	install pixku $(HOME)/.runt/bin

clean: 
	rm -rf pixku $(OBJ)
	rm -rf pixku.so
