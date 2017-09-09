#include <stdio.h>
#include <stdlib.h>
#include <runt.h>
#include <math.h>
#include "pixku.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    runt_float max;
    runt_float phs;
} pku_orbit;

static void orbit_init(pku_orbit *orb)
{
    orb->max = 0;
    orb->phs = 0;
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
    runt_int rc;
    runt_stacklet *s;
    runt_int mode;
    runt_float sn, cs;
    runt_float inc;
    pku_orbit *orb;
    runt_float max;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    mode = s->f;
    orb = runt_to_cptr(p);

    switch(mode) {
        case 0: /* initialize */
            rc = runt_ppop(vm, &s);
            RUNT_ERROR_CHECK(rc);
            max = s->f;
            orb->max = max;
            break;
        case 1: /* step */
            rc = runt_ppop(vm, &s);
            RUNT_ERROR_CHECK(rc);
            inc = s->f;
            sn = sin(orb->phs);
            cs = cos(orb->phs);

            rc = runt_ppush(vm, &s);
            RUNT_ERROR_CHECK(rc);
            s->f = cs;
            
            rc = runt_ppush(vm, &s);
            RUNT_ERROR_CHECK(rc);
            s->f = sn;
            
            orb->phs += inc * orb->max;
            orb->phs = fmod(orb->phs, 2*M_PI);

            break;
    }

    return RUNT_OK;
}

int pixku_orbit(runt_vm *vm)
{
    runt_word_define_with_copy(vm, "pixku_orbit", 11, 
        rproc_orbit, rcopy_orbit);
    return runt_is_alive(vm);
}
