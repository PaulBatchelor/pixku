PIXKU ?=../pixku
NAME ?= default

FFMPEG_OPTIONS=-i tmp.ogg -framerate 30 
FFMPEG_OPTIONS+=-i %04d.png -c:v libx264 -c:a copy -y -strict -2

FFMPEG_GIF_OPTIONS=-i palette.png -filter_complex paletteuse -r 10 -s 480x240

RUNT_OTHER?=

default: $(NAME).mp4

$(NAME).wav: $(NAME).rnt $(RUNT_OTHER)
	$(PIXKU) $<

%.mp4: %.wav
	sox $< -c 2 tmp.wav
	oggenc tmp.wav
	ffmpeg  $(FFMPEG_OPTIONS) $@
	rm tmp.wav tmp.ogg

%.gif: %.mp4
	ffmpeg -y -i $< -vf palettegen palette.png
	ffmpeg -y -i $< $(FFMPEG_GIF_OPTIONS) $@

clean:
	rm -rf $(NAME).wav
	rm -rf *.png
	rm -rf *.mp4
