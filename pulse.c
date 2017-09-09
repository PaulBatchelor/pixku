#include <stdio.h>
#include <stdlib.h>
#include <runt.h>
#include "pixku.h"

static runt_int rcopy_pulse(runt_vm *vm, runt_cell *src, runt_cell *dst)
{
    return RUNT_OK;
}

static runt_int rproc_pulse(runt_vm *vm, runt_ptr p)
{
    return RUNT_OK;
}

int pixku_pulse(runt_vm *vm)
{
    runt_word_define_with_copy(vm, "pixku_pulse", 13, 
        rproc_pulse, rcopy_pulse);
    return runt_is_alive(vm);
}
