#include <stdio.h>
#include <stdlib.h>
#include <runt.h>
#include "pixku.h"

typedef struct {
    runt_int max;
    runt_int pos;
    runt_int size;
    runt_int off;
    runt_float step;
    runt_float *buf;
} circbuf;

static runt_int rcopy_circbuf(runt_vm *vm, runt_cell *src, runt_cell *dst)
{
    dst->fun = src->fun;
    return RUNT_OK;
}

static runt_int rproc_circbuf(runt_vm *vm, runt_ptr p)
{
    return RUNT_OK;
}

int pixku_circbuf(runt_vm *vm)
{
    runt_word_define_with_copy(vm, "pixku_circbuf", 13, 
        rproc_circbuf, rcopy_circbuf);
    return runt_is_alive(vm);
}
