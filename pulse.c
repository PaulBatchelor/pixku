#include <stdio.h>
#include <stdlib.h>
#include <runt.h>
#include "pixku.h"

typedef struct {
    runt_float step;
    runt_float val;
    runt_int is_running;
} pku_pulse;

static void pulse_init(pku_pulse *pls)
{
    pls->step = 0;
    pls->val = 0;
    pls->is_running = 0;
}

static runt_int rcopy_pulse(runt_vm *vm, runt_cell *src, runt_cell *dst)
{
    pku_pulse *pls;
    runt_uint id;

    id = runt_malloc(vm, sizeof(pku_pulse), (void **)&pls);
    if(id == 0) return RUNT_NOT_OK;

    pulse_init(pls);
    dst->fun = src->fun;
    dst->p = runt_mk_cptr(vm, pls);
    return RUNT_OK;
}

static runt_int rproc_pulse(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_int mode;
    runt_stacklet *s;
    pku_pulse *pls;
    runt_float step;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    mode = s->f;

    pls = runt_to_cptr(p);

    switch(mode) {
        case 0:
            /* Initialize pulse
             *
             * step 0 pixku_pulse
             */ 

            rc = runt_ppop(vm, &s);
            RUNT_ERROR_CHECK(rc);
            step = s->f;
            pls->step = step;

            break;
        case 1:
            /* Actually perform tick */
            rc = runt_ppush(vm, &s);
            RUNT_ERROR_CHECK(rc);

            if(pls->is_running) {
                s->f = pls->val;
                pls->val *= pls->step;
                if(pls->val < 0.004) pls->is_running = 0;
            } else {
                s->f = 0;
            }

            break;
        case 2:
            /* Reset to zero */
            pls->val = 1;
            pls->is_running = 1;
            break;
    } 

    return RUNT_OK;
}

int pixku_pulse(runt_vm *vm)
{
    runt_word_define_with_copy(vm, "pixku_pulse", 11, 
        rproc_pulse, rcopy_pulse);
    return runt_is_alive(vm);
}
