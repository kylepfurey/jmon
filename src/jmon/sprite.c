// .c
// Jokémon Sprites
// by Kyle Furey

#include <jmon/jmon.h>

#pragma bank 0

/** Loads one or more sprite tiles into background VRAM. */
void jmon_load_background_tiles(byte_t index, const byte_t* tiles, byte_t count) NONBANKED {
	if (tiles == NULL || count == 0) {
		return;
	}
	set_bkg_data(index, count, tiles);
}

/** Loads one or more sprite tiles into object VRAM. */
void jmon_load_object_tiles(byte_t index, const byte_t* tiles, byte_t count) NONBANKED {
	if (tiles == NULL || count == 0) {
		return;
	}
	set_sprite_data(index, count, tiles);
}
