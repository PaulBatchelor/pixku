#include <stdio.h>
#include <stdlib.h>
#include <runt.h>
#include <cray.h>
#include <img.h>

#include "pixku.h"

runt_int runt_load_img(runt_vm *vm);
runt_int runt_load_cray(runt_vm *vm);
runt_int runt_load_cairo(runt_vm *vm);

static void bgcolor(cray_scene *scene, cray_ray *ray, int x, int y, CRAYFLT *color)
{
    unsigned char *clr;
    CRAYFLT k;

    k = 1.0/255.0;
    img_get(x, 255 - y, &clr);
    color[0] = clr[0] * k;
    color[1] = clr[1] * k;
    color[2] = clr[2] * k;

}

static void shadow(cray_scene *scene, CRAYFLT *color, int x, int y)
{
    unsigned char *clr;
    CRAYFLT k;

    k = 1.0/255.0;
    img_get(x, 255 - y, &clr);
    color[0] = clr[0] * k;
    color[1] = clr[1] * k;
    color[2] = clr[2] * k;
}

static runt_int rproc_blk(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    runt_int x;
    runt_int y;
    runt_int ix;
    runt_int iy;
    runt_int pos;
    runt_int r, g, b;
    cray_scene *scene;
    CRAYFLT *buf;

    buf = calloc(sizeof(CRAYFLT), 8 * 8 * 3);

    scene = cray_get();
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    y = s->f;
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    x = s->f;

    cray_scene_render(scene, x * 8, y * 8, 8, 8, buf,
        CRAY_SEGMENT);

    for(iy = 7; iy >=0; iy--) {
        for(ix = 0; ix < 8; ix++) {
            pos = iy * 8 * 3 + ix * 3;
            r = (int)(255.99 * buf[pos]);
            g = (int)(255.99 * buf[pos + 1]);
            b = (int)(255.99 * buf[pos + 2]);
            set_color_rgb(r, g, b);
            img_point(x * 8 + ix, y * 8 + iy);
        }
    }

    free(buf);
    return RUNT_OK;
}

static runt_int rproc_render(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    runt_int x, y;
    runt_int w, h;
    runt_int ix;
    runt_int iy;
    runt_int pos;
    runt_int r, g, b;
    cray_scene *scene;
    CRAYFLT *buf;

    scene = cray_get();
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    h = s->f;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    w = s->f;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    y = s->f;
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    x = s->f;

    buf = calloc(sizeof(CRAYFLT), w * h * 3);
    cray_scene_render(scene, x, y, w, h, buf,
        CRAY_SEGMENT);


    for(iy = h - 1; iy >=0; iy--) {
        for(ix = 0; ix < w; ix++) {
            pos = iy * w * 3 + ix * 3;
            r = (int)(255.99 * buf[pos]);
            g = (int)(255.99 * buf[pos + 1]);
            b = (int)(255.99 * buf[pos + 2]);
            set_color_rgb(r, g, b);
            img_point(x + ix, y + iy);
        }
    }

    free(buf);
    return RUNT_OK;
}

static runt_int rproc_glyph(runt_vm *vm, runt_ptr p)
{
    runt_int rc;
    runt_stacklet *s;
    runt_int x;
    runt_int y;
    runt_int ix;
    runt_int iy;
    runt_int pos;
    cray_scene *scene;
    CRAYFLT *buf;
    runt_float lum;
    runt_float thresh;

    buf = calloc(sizeof(CRAYFLT), 8 * 8 * 3);

    scene = cray_get();

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    thresh = s->f;

    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    y = s->f;
    
    rc = runt_ppop(vm, &s);
    RUNT_ERROR_CHECK(rc);
    x = s->f;

    cray_scene_render(scene, x * 8, y * 8, 8, 8, buf,
        CRAY_SEGMENT);

    for(iy = 7; iy >=0; iy--) {
        for(ix = 0; ix < 8; ix++) {
            pos = iy * 8 * 3 + ix * 3;
            lum = 0.2125 * buf[pos] + 
                0.7152 * buf[pos + 1] + 
                0.0722 * buf[pos + 2];

            if(lum < thresh) {
                img_point(x * 8 + ix, y * 8 + iy);
            }

        }
    }

    free(buf);
    return RUNT_OK;
}

static int rproc_bgcolor(runt_vm *vm, runt_ptr p)
{
    cray_scene *scene;
    scene = cray_get();
    cray_scene_cb_bgcolor(scene, bgcolor);
    return RUNT_OK;
}

static int rproc_shadow(runt_vm *vm, runt_ptr p)
{
    cray_scene *scene;
    scene = runt_to_cptr(p);
    scene = cray_get();
    cray_scene_cb_shadow(scene, shadow);
    return RUNT_OK;
}

static int rproc_loadimg(runt_vm *vm, runt_ptr p)
{
    runt_load_img(vm);
    runt_mark_set(vm);
    return RUNT_OK;
}

static int rproc_loadcairo(runt_vm *vm, runt_ptr p)
{
    runt_load_cairo(vm);
    runt_mark_set(vm);
    return RUNT_OK;
}

static int rproc_loadcray(runt_vm *vm, runt_ptr p)
{
    runt_load_cray(vm);
    runt_word_define(vm, "pix_blk", 7, rproc_blk);
    runt_word_define(vm, "pix_render", 10, rproc_render);
    runt_word_define(vm, "pix_glyph", 9, rproc_glyph);
    runt_word_define(vm, "pix_bgcolor", 11, rproc_bgcolor);
    runt_word_define(vm, "pix_shadow", 10, rproc_shadow);
    runt_mark_set(vm);
    return RUNT_OK;
}

int pixku_runt_loader(runt_vm *vm)
{
    runt_load_stdlib(vm);

    runt_word_define(vm, "pix_img", 7, rproc_loadimg);
    runt_word_define(vm, "pix_cray", 8, rproc_loadcray);
    runt_word_define(vm, "pix_cairo", 9, rproc_loadcairo);
    return RUNT_OK;
}

