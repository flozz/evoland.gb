PROG = evoland
CC = ./gbdk-n/bin/gbdk-n-compile.sh
LL = ./gbdk-n/bin/gbdk-n-link.sh
MR = ./gbdk-n/bin/gbdk-n-make-rom.sh
_OBJ = $(patsubst %.c,%.rel,$(wildcard src/*.c))

all: build

run: build
	mednafen $(PROG).gb

build: $(PROG).gb

$(PROG).gb: $(_OBJ)
	$(LL) -Wl-m -o $(PROG).ihx $^
	$(MR) $(PROG).ihx $(PROG).gb

src/%.rel: src/%.c
	$(CC) -Wa-l -o $@ -c $<

gassets:
	img2gb tileset \
		--output-c-file=src/background.tileset.c \
		--output-header-file=src/background.tileset.h \
		--output-image=src/background.tileset.png \
		--name BG_TILESET \
		./background-tileset.png
	img2gb tilemap \
		--output-c-file=src/background.tilemap.c \
		--output-header-file=src/background.tilemap.h \
		--name BG_TILEMAP \
		src/background.tileset.png \
		./background-tilemap.png

gbdk-n-lib:
	cd ./gbdk-n/ && make

clean:
	rm -rf src/*.rel
	rm -rf src/*.lst
	rm -rf src/*.sym
	rm -rf src/*.asm
	rm -rf $(PROG).gb
	rm -rf $(PROG).ihx
	rm -rf $(PROG).map
	rm -rf $(PROG).sym
	rm -rf $(PROG).noi
	rm -rf $(PROG).lk
