PIXKU=pixku

FFMPEG_OPTIONS=-i tmp.wav -framerate 30 
FFMPEG_OPTIONS+=-i %04d.png -c:v libx264 -c:a aac -y -strict -2

ll.wav: ll.rnt
	$(PIXKU) $<

%.mp4: %.wav
	sox $< -c 2 tmp.wav
	ffmpeg  $(FFMPEG_OPTIONS) $@
	rm tmp.wav

clean:
	rm -rf ll.wav
	rm -rf *.png
	rm -rf *.mp4
