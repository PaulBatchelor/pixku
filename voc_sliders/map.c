#include <stdio.h>
#include <runt.h>
#include <soundpipe.h>
#include <sporth.h>
#include "voc.h"

static runt_int rproc_vocmap(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    sp_voc *voc;
    runt_uint id;
    int i;
    int size;
    SPFLOAT *diameters;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    voc = runt_to_cptr(s->p);

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    id = s->f;

    size = sp_voc_get_tract_size(voc);
    diameters = sp_voc_get_tract_diameters(voc);

    for(i = 0; i < size; i++) {
        rc = runt_ppush(vm, &s);
        RUNT_ERROR_CHECK(rc);
        s->f = (runt_float) diameters[i];
        runt_cell_id_exec(vm, id);
    }

    return RUNT_OK;
}

static runt_int rproc_vocdata(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    sp_voc *voc;
    int size;
    sporth_fload_d *fdata;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    fdata = runt_to_cptr(s->p);
    voc = fdata->ud;

    size = sp_voc_get_tract_size(voc);

    runt_print(vm, "the tract size is %d\n", size);

    rc = runt_ppush(vm, &s);
    RUNT_ERROR_CHECK(rc);
    s->p = runt_mk_cptr(vm, voc);

    return RUNT_OK;
}

static runt_int rproc_plumbstep(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    plumber_data *pd;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    pd = runt_to_cptr(s->p);

    plumber_compute(pd, PLUMBER_COMPUTE);
    sporth_stack_pop_float(&pd->sporth.stack);

    return RUNT_OK;
}

void runt_plugin_init(runt_vm *vm)
{
    runt_print(vm, "loading custom voc plugins...\n");
    runt_word_define(vm, "vocmap", 6, rproc_vocmap);
    runt_word_define(vm, "vocdata", 7, rproc_vocdata);
    runt_word_define(vm, "plumbstep", 9, rproc_plumbstep);
}
