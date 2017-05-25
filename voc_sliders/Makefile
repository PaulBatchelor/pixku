.PHONY: render 

PIXKU=../pixku
FFMPEG_OPTIONS=-i tmp.wav -framerate 30 
FFMPEG_OPTIONS+=-i %04d.png -c:v libx264 -c:a aac -y -strict -2

default: chant babble unya

slider_test:
	$(PIXKU) $@.rnt
	make $@.mp4

chant:
	$(PIXKU) $@.rnt
	make $@.mp4

babble:
	$(PIXKU) $@.rnt
	make $@.mp4

unya:
	$(PIXKU) $@.rnt
	make $@.mp4

%.mp4: 
	sox out.wav -c 2 tmp.wav
	ffmpeg  $(FFMPEG_OPTIONS) $@
	rm tmp.wav

cleanup:
	rm -rf *.png
	rm -rf out.wav

clean: 
	make cleanup
	rm -rf slider_test.mp4
	rm -rf chant.mp4
	rm -rf babble.mp4
	rm -rf unya.mp4
