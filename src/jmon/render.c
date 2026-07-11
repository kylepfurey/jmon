// .c
// Jokémon Rendering
// by Kyle Furey

#include <jmon/jmon.h>

/** Initializes rendering. */
void jmon_init(void) NONBANKED {
	DISPLAY_OFF;
	if (DEVICE_SUPPORTS_COLOR) {
		set_default_palette();
	}
	DISPLAY_ON;
}

/** Advances to the next frame. */
void jmon_next_frame(void) NONBANKED {
	vsync();
}
