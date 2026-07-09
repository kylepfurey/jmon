// .c
// Jokémon Entry Point
// by Kyle Furey

#include <jmon/jmon.h>

/** Game loop. */
void main(void) {
	printf("Welcome to Jokemon!\n");
	while (true) {
		wait_vbl_done();
	}
}
