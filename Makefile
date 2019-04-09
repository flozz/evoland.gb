PROG = evoland
CC = ./gbdk-n/bin/gbdk-n-compile.sh -DDEBUG
LL = ./gbdk-n/bin/gbdk-n-link.sh
MR = ./gbdk-n/bin/gbdk-n-make-rom.sh
_OBJ = $(patsubst %.c,%.rel,$(wildcard src/*.c)) $(patsubst %.c,%.rel,$(wildcard src/*/*.c))

all: build

run: build
	mednafen $(PROG).gb

build: $(PROG).gb

$(PROG).gb: $(_OBJ)
	$(LL) -o $(PROG).ihx $^
	$(MR) $(PROG).ihx $(PROG).gb
	./maptosym/maptosym.py $(PROG).map

src/%.rel: src/%.c
	$(CC) -o $@ -c $<

.PHONY: gassets
gassets:
	img2gb tileset \
		--output-c-file=src/gassets/background.tileset.c \
		--output-header-file=src/gassets/background.tileset.h \
		--output-image=src/gassets/background.tileset.png \
		--name BG_TILESET \
		./gassets/background-tileset.png
	img2gb tilemap \
		--output-c-file=src/gassets/background.tilemap.c \
		--output-header-file=src/gassets/background.tilemap.h \
		--name BG_TILEMAP \
		./src/gassets/background.tileset.png \
		./gassets/background-tilemap.png
	img2gb tileset \
		--output-c-file=src/gassets/sprites.tileset.c \
		--output-header-file=src/gassets/sprites.tileset.h \
		--output-image=src/gassets/sprites.tileset.png \
		--sprite8x16 \
		--name SPRITES \
		./gassets/sprites.png
	img2gb tileset \
		--output-c-file=src/gassets/evoland_logo.tileset.c \
		--output-header-file=src/gassets/evoland_logo.tileset.h \
		--output-image=src/gassets/evoland_logo.tileset.png \
		--name EVOLAND_LOGO_TILESET \
		--deduplicate \
		./gassets/evoland-logo.png
	img2gb tilemap \
		--output-c-file=src/gassets/evoland_logo.tilemap.c \
		--output-header-file=src/gassets/evoland_logo.tilemap.h \
		--name EVOLAND_LOGO_TILEMAP \
		./src/gassets/evoland_logo.tileset.png \
		./gassets/evoland-logo.png
	img2gb tileset \
		--output-c-file=src/gassets/font.tileset.c \
		--output-header-file=src/gassets/font.tileset.h \
		--output-image=src/gassets/font.tileset.png \
		--name FONT_TILESET \
		./gassets/font.png

objects:
	./scripts/extract-objects.py \
		Chests \
		CHESTS \
		./gassets/background-tilemap.tmx \
		./src/objects/chests.objects.c \
		./src/objects/chests.objects.h

gbdk-n-lib:
	cd ./gbdk-n/ && make

clean:
	rm -rf src/*.rel
	rm -rf src/*.lst
	rm -rf src/*.sym
	rm -rf src/*.asm
	rm -rf src/*/*.rel
	rm -rf src/*/*.lst
	rm -rf src/*/*.sym
	rm -rf src/*/*.asm
	rm -rf $(PROG).gb
	rm -rf $(PROG).ihx
	rm -rf $(PROG).map
	rm -rf $(PROG).sym
	rm -rf $(PROG).noi
	rm -rf $(PROG).lk
