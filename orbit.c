#include <stdio.h>
#include <stdlib.h>
#include <runt.h>
#include "pixku.h"

typedef struct {
    runt_float step;
    runt_float val;
    runt_int is_running;
} pku_orbit;

static void orbit_init(pku_orbit *orb)
{
}

static runt_int rcopy_orbit(runt_vm *vm, runt_cell *src, runt_cell *dst)
{
    pku_orbit *orb;
    runt_uint id;

    id = runt_malloc(vm, sizeof(pku_orbit), (void **)&orb);
    if(id == 0) return RUNT_NOT_OK;

    orbit_init(orb);
    dst->fun = src->fun;
    dst->p = runt_mk_cptr(vm, orb);
    return RUNT_OK;
}

static runt_int rproc_orbit(runt_vm *vm, runt_ptr p)
{
    return RUNT_OK;
}

int pixku_orbit(runt_vm *vm)
{
    runt_word_define_with_copy(vm, "pixku_orbit", 11, 
        rproc_orbit, rcopy_orbit);
    return runt_is_alive(vm);
}
