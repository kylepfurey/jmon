// .c
// Jokémon Color
// by Kyle Furey

#include <jmon/jmon.h>

#pragma bank 0

/** Is Jokémon running on GameBoy Color? */
bool_t jmon_is_gbc(void) NONBANKED {
	return DEVICE_SUPPORTS_COLOR;
}

/** Loads one or more palettes into background VRAM. */
void jmon_load_background_palettes(byte_t index, const palette_color_t* palettes, byte_t count) NONBANKED {
	if (!DEVICE_SUPPORTS_COLOR || palettes == NULL || count == 0 || index >= PALETTE_COUNT) {
		return;
	}
	set_bkg_palette(index, count, palettes);
}

/** Loads one or more palettes into object VRAM. */
void jmon_load_object_palettes(byte_t index, const palette_color_t* palettes, byte_t count) NONBANKED {
	if (!DEVICE_SUPPORTS_COLOR || palettes == NULL || count == 0 || index >= PALETTE_COUNT) {
		return;
	}
	set_sprite_palette(index, count, palettes);
}
