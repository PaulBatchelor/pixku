.PHONY: render 

PIXKU=../pixku -c 1024
FFMPEG_OPTIONS=-i tmp.wav -framerate 30 
FFMPEG_OPTIONS+=-i %04d.png -c:v libx264 -c:a aac -y -strict -2

default: chant_sliders babble_sliders unya_sliders map.so\
	chant_plot unya_plot babble_plot

CFLAGS=-I$(HOME)/.runt/include  -Wall -g
LDFLAGS = -L$(HOME)/.runt/lib -lrunt libvoc.a -lsporth -lsoundpipe 

slider_test:
	$(PIXKU) $@.rnt
	make $@.mp4

chant_sliders:
	$(PIXKU) $@.rnt
	make $@.mp4

babble_sliders:
	$(PIXKU) $@.rnt
	make $@.mp4

unya_sliders:
	$(PIXKU) $@.rnt
	make $@.mp4

babble_plot: map.so
	$(PIXKU) $@.rnt
	make $@.mp4

chant_plot: map.so
	$(PIXKU) $@.rnt
	make $@.mp4

unya_plot: map.so
	$(PIXKU) $@.rnt
	make $@.mp4

%.mp4: 
	sox out.wav -c 2 tmp.wav
	ffmpeg  $(FFMPEG_OPTIONS) $@
	rm tmp.wav


map.so: map.c
	$(CC) $< $(CFLAGS) -shared -fPIC -o $@ $(LDFLAGS)

cleanup:
	rm -rf *.png
	rm -rf out.wav

clean: 
	make cleanup
	rm -rf slider_test.mp4
	rm -rf chant_sliders.mp4
	rm -rf babble_sliders.mp4
	rm -rf unya_sliders.mp4
	rm -rf chant_plot.mp4
	rm -rf babble_plot.mp4
	rm -rf unya_plot.mp4
	rm -rf map.so
