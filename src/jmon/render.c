// .c
// Jokémon Rendering
// by Kyle Furey

#include <jmon/jmon.h>

#pragma bank 0

/** Initializes rendering. */
void jmon_init(void) NONBANKED {
	DISPLAY_OFF;
	LCDC_REG |= LCDCF_BG8000;
	if (DEVICE_SUPPORTS_COLOR) {
		set_default_palette();
	}
	else {
		BGP_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
		OBP0_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
		OBP1_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
	}
	NR52_REG = 0x80;
	NR50_REG = 0x77;
	NR51_REG = 0xFF;
	SHOW_BKG;
	HIDE_WIN;
	SHOW_SPRITES;
	DISPLAY_ON;
}

/** Advances to the next frame. */
void jmon_next_frame(void) NONBANKED {
	vsync();
}
