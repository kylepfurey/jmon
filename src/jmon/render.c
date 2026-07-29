// .c
// Jokémon Rendering
// by Kyle Furey

#include <jmon/jmon.h>

#pragma bank 0

/** Initializes rendering. */
void jmon_init(void) NONBANKED {
	DISPLAY_OFF;
	if (DEVICE_SUPPORTS_COLOR) {
		set_default_palette();
	}
	DISPLAY_ON;
	NR52_REG = 0x80;
	NR50_REG = 0x77;
	NR51_REG = 0xFF;
}

/** Advances to the next frame. */
void jmon_next_frame(void) NONBANKED {
	vsync();
}
