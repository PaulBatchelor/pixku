#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <soundpipe.h>
#include <sporth.h>
#include <string.h>
#include <runt.h>
#include "pixku.h"

static runt_int get_id(runt_vm *vm, const char *name, runt_uint *id)
{
    runt_entry *e;
    if(runt_word_search(vm, name, strlen(name), &e) != RUNT_OK) {
        return RUNT_NOT_OK;
    } else {
        *id = e->cell->id;
        return RUNT_OK;
    }
    
}

int pixku_init(pixku_data *pix, 
        const char *file, 
        const char *draw, 
        const char *clean)
{
    int rc;
    runt_vm *vm;

    vm = &pix->vm;

    runt_init(vm);

    pix->cells = malloc(sizeof(runt_cell) * PIX_NCELLS);
    pix->mem = malloc(sizeof(char) * PIX_MEMSIZE);

    runt_cell_pool_set(vm, pix->cells, PIX_NCELLS);
    runt_cell_pool_init(vm);

    runt_memory_pool_set(vm, pix->mem, PIX_MEMSIZE);

    pixku_runt_loader(vm);
    runt_mark_set(vm);

    runt_set_state(vm, RUNT_MODE_INTERACTIVE, RUNT_ON);
    if(runt_parse_file(vm, file) != RUNT_OK) {
        return RUNT_NOT_OK;
    }

    rc = get_id(vm, draw, &pix->draw);
    if(rc != RUNT_OK) {
        runt_print(vm, "Could not find draw function '%s'\n", draw);
        return RUNT_NOT_OK;
    }
    
    rc = get_id(vm, clean, &pix->clean);
    if(rc != RUNT_OK) {
        runt_print(vm, "Could not find clean function '%s'\n", clean);
        return RUNT_NOT_OK;
    }


    return RUNT_OK;
}

void pixku_draw(pixku_data *pix)
{
}

void pixku_clean(pixku_data *pix)
{
    free(pix->cells);
    free(pix->mem);
}

static int sporth_pix(plumber_data *pd, sporth_stack *stack, void **ud)
{
    pixku_data *pix;
    SPFLOAT trig;
    const char *draw;
    const char *clean;
    const char *file;
    switch(pd->mode) {
        case PLUMBER_CREATE:
            if(sporth_check_args(stack, "fsss") != SPORTH_OK) {
                fprintf(stderr,"Not enough arguments for gain\n");
                stack->error++;
                return PLUMBER_NOTOK;
            }
            /* malloc and assign address to user data */
            pix = malloc(sizeof(pixku_data));
            *ud = pix;

            sporth_stack_pop_string(stack);
            sporth_stack_pop_string(stack);
            sporth_stack_pop_string(stack);
            sporth_stack_pop_float(stack);
            break;
        case PLUMBER_INIT:
            pix = *ud;
            clean = sporth_stack_pop_string(stack);
            draw = sporth_stack_pop_string(stack);
            file = sporth_stack_pop_string(stack);
            sporth_stack_pop_float(stack);
            pixku_init(pix, file, draw, clean);
            trig = sporth_stack_pop_float(stack);
            break;

        case PLUMBER_COMPUTE:
            trig = sporth_stack_pop_float(stack);
            if(trig != 0) {
                pix = *ud;
                pixku_draw(pix);
            }
            break;

        case PLUMBER_DESTROY:
            pix = *ud;
            pixku_clean(pix);
            free(*ud);
            break;
        default:
            fprintf(stderr, "gain: unknown mode!\n");
            break;
    }
    return PLUMBER_OK;
}

plumber_dyn_func sporth_return_ugen()
{
    return sporth_pix;
}
