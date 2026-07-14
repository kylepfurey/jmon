// .c
// Jokémon Color
// by Kyle Furey

#include <jmon/jmon.h>

#pragma bank 0

/** Is Jokémon running on GameBoy Color? */
bool_t jmon_is_gbc(void) NONBANKED {
	return DEVICE_SUPPORTS_COLOR;
}
