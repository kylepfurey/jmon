// .c
// Jokémon Entry Point
// by Kyle Furey

#include <jmon/jmon.h>

#pragma bank 0

/** Game loop. */
void main(void) NONBANKED {
	jmon_init();
	input_t input = { 0 };
	while (true) {
		jmon_next_frame();
		jmon_update_input(&input);
	}
}
