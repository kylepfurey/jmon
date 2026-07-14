// .c
// Jokémon Entry Point
// by Kyle Furey

#include <jmon/jmon.h>

/** Game loop. */
void main(void) NONBANKED {
	jmon_init();
	while (true) {
		jmon_next_frame();
	}
}
