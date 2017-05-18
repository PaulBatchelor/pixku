.PHONY: render 

PIXKU=../pixku
FFMPEG_OPTIONS=-i tmp.wav -framerate 30 
FFMPEG_OPTIONS+=-i %04d.png -c:v libx264 -c:a aac -y -strict -2


render: 
	$(PIXKU) circ_rot.rnt
	make circ_rot.mp4
	$(PIXKU) circ.rnt
	make circ.mp4

%.mp4: 
	sox out.wav -c 2 tmp.wav
	ffmpeg  $(FFMPEG_OPTIONS) $@
	rm tmp.wav

clean: 
	rm -rf *.png
	rm -rf out.wav
	rm -rf circ.mp4
	rm -rf circ_rot.mp4
