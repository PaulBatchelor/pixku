#ifndef PIXKU_H
#define PIXKU_H

#define PIX_NCELLS 512
#define PIX_MEMSIZE RUNT_MEGABYTE

typedef struct {
    runt_vm vm;
    runt_cell *cells;
    unsigned char *mem;
    runt_uint draw;
    runt_uint clean;
} pixku_data;

int pixku_runt_loader(runt_vm *vm);

int pixku_init(pixku_data *pix, 
        const char *file, 
        const char *draw, 
        const char *clean);

void pixku_draw(pixku_data *pix);
void pixku_clean(pixku_data *pix);

#endif
