SRC = \
	src/main.cpp \
	src/game.cpp \
	src/mylib/core.cpp \
	src/mylib/graphics.cpp \
	src/mylib/audio.cpp \
	src/mylib/clock.cpp \
	src/mylib/callbacks.cpp \
	src/invaders/player.cpp \
	src/invaders/enemy.cpp \
	src/states/gameplay.cpp \
	src/states/title.cpp \
	src/states/end.cpp

INCLUDE = -Iinclude -I.

LIBS = \
	external/SDL3/libSDL3.a \
	external/SDL3_image/libSDL3_image.a \
	external/SDL3_ttf/libSDL3_ttf.a \
	external/SDL3_mixer/libSDL3_mixer.a \
	-lharfbuzz -lfreetype

build:
	g++ $(SRC) -o game $(INCLUDE) $(LIBS)





SHELLFILE = --shell-file minshell.html

WEB_LIBS = \
		-Lexternal-web/SDL3-web \
		-Lexternal-web/SDL3_image-web \
		-Lexternal-web/SDL3_mixer-web \
		-Lexternal-web/SDL3_ttf-web

WEB_FLAGS = \
		-lSDL3 -lSDL3_image -lSDL3_mixer -lSDL3_ttf \
		-lpng -lz -lmpg123 -lfreetype -lharfbuzz \
		-sALLOW_MEMORY_GROWTH=1

web-build:
	em++ $(INCLUDE) $(SRC) -o web/index.html $(WEB_LIBS) $(WEB_FLAGS) $(SHELLFILE) -DPLATFORM_WEB --preload-file assets
