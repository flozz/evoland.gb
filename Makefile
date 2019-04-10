PROG = evoland
CC = ./gbdk-n/bin/gbdk-n-compile.sh -DDEBUG
LL = ./gbdk-n/bin/gbdk-n-link.sh
MR = ./gbdk-n/bin/gbdk-n-make-rom.sh
_OBJ = $(patsubst %.c,%.rel,$(wildcard src/*.c)) $(patsubst %.c,%.rel,$(wildcard src/gassets/*.c)) $(patsubst %.c,%.rel,$(wildcard src/objects/*.c))
_OBJ_EN = $(patsubst %.c,%.rel,$(wildcard src/locales/*.en.c))
_OBJ_FR = $(patsubst %.c,%.rel,$(wildcard src/locales/*.fr.c))

all: build

run: build
	mednafen $(PROG)_en.gb

build: $(PROG)_en.gb $(PROG)_fr.gb

$(PROG)_en.gb: $(_OBJ) $(_OBJ_EN)
	$(LL) -o $(PROG)_en.ihx $^
	$(MR) $(PROG)_en.ihx $(PROG)_en.gb
	./maptosym/maptosym.py $(PROG)_en.map

$(PROG)_fr.gb: $(_OBJ) $(_OBJ_FR)
	$(LL) -o $(PROG)_fr.ihx $^
	$(MR) $(PROG)_fr.ihx $(PROG)_fr.gb
	./maptosym/maptosym.py $(PROG)_fr.map

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
	rm -rf $(PROG)_*.gb
	rm -rf $(PROG)_*.ihx
	rm -rf $(PROG)_*.map
	rm -rf $(PROG)_*.sym
	rm -rf $(PROG)_*.noi
	rm -rf $(PROG)_*.lk
