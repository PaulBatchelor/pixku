#ifndef PIXKU_H
#define PIXKU_H

typedef struct {
    runt_vm vm;
    runt_cell *cells;
    unsigned char *mem;
    runt_uint draw;
    runt_uint clean;
} pixku_data;

int pixku_runt_loader(runt_vm *vm);

#endif
