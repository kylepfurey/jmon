// .c
// Jokémon Entry Point
// by Kyle Furey

#include <jmon/jmon.h>

#pragma bank BANK_STATIC

/** Game loop. */
void main(void) NONBANKED {
	jmon_init();
	printf("Welcome to Jokemon!\n");
	while (true) {
		jmon_next_frame();
	}
}
