// .c
// Jokémon Color
// by Kyle Furey

#include <jmon/jmon.h>

/** Is Jokémon running on GameBoy Color? */
bool_t jmon_is_gbc(void) NONBANKED {
	return DEVICE_SUPPORTS_COLOR;
}
