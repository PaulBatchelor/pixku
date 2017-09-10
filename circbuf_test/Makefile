PIXKU=../pixku

FFMPEG_OPTIONS=-i tmp.wav -framerate 30 
FFMPEG_OPTIONS+=-i %04d.png -c:v libx264 -c:a aac -y -strict -2

NAME=circbuf

default: circbuf.mp4

$(NAME).wav: $(NAME).rnt
	$(PIXKU) $<

%.mp4: %.wav
	sox $< -c 2 tmp.wav
	ffmpeg  $(FFMPEG_OPTIONS) $@
	rm tmp.wav

clean:
	rm -rf $(NAME).wav
	rm -rf *.png
	rm -rf *.mp4
	rm -rf *.gif
	rm -rf *.png
