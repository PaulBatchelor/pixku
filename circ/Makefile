.PHONY: render

PIXKU=../pixku
FFMPEG_OPTIONS=-i tmp.wav -framerate 30 
FFMPEG_OPTIONS+=-i %04d.png -c:v libx264 -c:a aac -y -strict -2

render: 
	$(PIXKU) circ.rnt
	make out.mp4

out.mp4: 
	sox out.wav -c 2 tmp.wav
	ffmpeg  $(FFMPEG_OPTIONS) out.mp4
	rm tmp.wav

clean: 
	rm *.png
	rm out.wav
	rm out.mp4
