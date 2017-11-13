PIXKU=../pixku

FFMPEG_OPTIONS=-i tmp.ogg -framerate 30 
FFMPEG_OPTIONS+=-i %04d.png -c:v libx264 -c:a copy -y -strict -2

NAME=pulse

default: $(NAME).mp4

$(NAME).wav: $(NAME).rnt
	$(PIXKU) $<

%.mp4: %.wav
	sox $< -c 2 tmp.wav
	oggenc tmp.wav
	ffmpeg  $(FFMPEG_OPTIONS) $@
	rm -f tmp.wav tmp.ogg

clean:
	rm -rf $(NAME).wav
	rm -rf *.png
	rm -rf *.mp4
