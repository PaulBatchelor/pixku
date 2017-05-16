OBJ=pixku.o

CFLAGS=-I$(HOME)/.runt/include 
LDFLAGS= -L$(HOME)/.runt/lib/ -lrunt -ldl -lrunt_img -lGL -lrunt_cray -lm

default: pixku

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

pixku: pixku.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean: 
	rm -rf pixku $(OBJ)
