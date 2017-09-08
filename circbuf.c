#include <stdio.h>
#include <stdlib.h>
#include <runt.h>
#include "pixku.h"

typedef struct {
    runt_int max;
    runt_int size;
    runt_int off;
    runt_int init;
    runt_float step;
    runt_float *buf;
    runt_uint fun;
    runt_uint insert;
} circbuf;

static void circbuf_init(circbuf *cb)
{
    cb->max = 0;
    cb->size = 0;
    cb->off = 0;
    cb->step = 0;
    cb->init = 1;
}

static runt_int rcopy_circbuf(runt_vm *vm, runt_cell *src, runt_cell *dst)
{
    circbuf *cb;
    runt_uint p;

    p = runt_malloc(vm, sizeof(circbuf), (void **)&cb);
    if(p == 0) return RUNT_NOT_OK;

    circbuf_init(cb);
    dst->fun = src->fun;
    dst->p = runt_mk_cptr(vm, cb);
    return RUNT_OK;
}

static runt_int rproc_circbuf(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_int mode;
    runt_stacklet *s;
    runt_uint fun;
    runt_uint insert;
    circbuf *cb;
    runt_int max;
    runt_float step;
    runt_float *buf;
    runt_int pos;
    runt_int i;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    mode = s->f;

    cb = runt_to_cptr(p);

    switch(mode) {
        case 0:
            /*
             * Initialize the circular buffer:
             * 
             * step max fun insert 0 pixku_cirbuf
             *
             */ 

            cb->init = 0;
            
            rc = runt_ppop(vm, &s);
            RUNT_ERROR_CHECK(rc);
            insert = s->f;
            
            rc = runt_ppop(vm, &s);
            RUNT_ERROR_CHECK(rc);
            fun = s->f;
            
            rc = runt_ppop(vm, &s);
            RUNT_ERROR_CHECK(rc);
            max = s->f;
            
            rc = runt_ppop(vm, &s);
            RUNT_ERROR_CHECK(rc);
            step = s->f;

            runt_malloc(vm, sizeof(runt_float) * max, (void **)&buf); 
            cb->max = max;
            cb->buf = buf;
            cb->fun = fun;
            cb->step = step;
            cb->insert = insert;
            runt_mark_set(vm);
            break;
        
        case 1:
            /* Append a value to the circular buf 
             *
             * No additional arguments:
             *
             * 1 pixku_circbuf
             *
             */
            if(cb->init) {
                runt_print(vm, "cirbuf: must be initialized\n");
                return RUNT_NOT_OK;
            }
          
            if(cb->size < cb->max) {
                cb->size++;
                pos = ((cb->size + cb->off) - 1) % cb->max;
                cb->buf[pos] = 1.0;

                rc = runt_ppush(vm, &s);
                RUNT_ERROR_CHECK(rc);
                s->f = pos;

                runt_cell_id_exec(vm, cb->insert);

            } else {
                runt_print(vm, "circbuf: at max!\n");
            }
            break;
        case 2: 
            /* Update and step through the circular buf 
             *
             * Also no arguments: 
             *
             * 2 pixku_cirbuf
             *
             */
            if(cb->init) {
                runt_print(vm, "cirbuf: must be initialized\n");
                return RUNT_NOT_OK;
            }
            for(i = 0; i < cb->size; i++) {
                pos = (i + cb->off) % cb->max;

                rc = runt_ppush(vm, &s);
                RUNT_ERROR_CHECK(rc);
                s->f = cb->buf[pos];

                rc = runt_ppush(vm, &s);
                RUNT_ERROR_CHECK(rc);
                s->f = pos;

                runt_cell_id_exec(vm, cb->fun);
                cb->buf[pos] *= cb->step;
                if(cb->buf[pos] < 0.001) {
                    /* "pop" current value from stack */
                    cb->off = (cb->off + 1) % cb->max;
                    cb->size--;
                }
            }

            break;

    } 

    return RUNT_OK;
}

int pixku_circbuf(runt_vm *vm)
{
    runt_word_define_with_copy(vm, "pixku_circbuf", 13, 
        rproc_circbuf, rcopy_circbuf);
    return runt_is_alive(vm);
}
