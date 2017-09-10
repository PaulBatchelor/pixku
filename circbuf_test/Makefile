PIXKU=../pixku

FFMPEG_OPTIONS=-i tmp.wav -framerate 30 
FFMPEG_OPTIONS+=-i %04d.png -c:v libx264 -c:a aac -y -strict -2

FFMPEG_GIF_OPTIONS=-i palette.png -filter_complex paletteuse -r 10 -s 480x320

NAME=circbuf

default: circbuf.mp4

$(NAME).wav: $(NAME).rnt
	$(PIXKU) $<

%.mp4: %.wav
	sox $< -c 2 tmp.wav
	ffmpeg  $(FFMPEG_OPTIONS) $@
	rm tmp.wav

%.gif: %.mp4
	ffmpeg -y -i $< -vf palettegen palette.png
	ffmpeg -y -i $< $(FFMPEG_GIF_OPTIONS) $@

clean:
	rm -rf $(NAME).wav
	rm -rf *.png
	rm -rf *.mp4
	rm -rf *.gif
	rm -rf *.png
