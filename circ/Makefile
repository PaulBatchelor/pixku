.PHONY: render 

PIXKU=../pixku
FFMPEG_OPTIONS=-i tmp.wav -framerate 30 
FFMPEG_OPTIONS+=-i %04d.png -c:v libx264 -c:a aac -y -strict -2

default: render_all

circ_color:
	$(PIXKU) $@.rnt
	make $@.mp4
	make cleanup

circ_rot:
	$(PIXKU) $@.rnt
	make $@.mp4
	make cleanup

circ:
	$(PIXKU) $@.rnt
	make $@.mp4
	make cleanup

render_all: circ circ_rot circ_color

%.mp4: 
	sox out.wav -c 2 tmp.wav
	ffmpeg  $(FFMPEG_OPTIONS) $@
	rm tmp.wav

cleanup:
	rm -rf *.png
	rm -rf out.wav

clean: 
	make cleanup
	rm -rf circ.mp4
	rm -rf circ_rot.mp4
	rm -rf circ_color.mp4
