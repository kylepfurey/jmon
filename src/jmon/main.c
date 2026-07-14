// .c
// Jokémon Entry Point
// by Kyle Furey

#include <jmon/jmon.h>

/** Game loop. */
void main(void) NONBANKED {
	jmon_init();
	volatile save_t* save = jmon_load(SAVE_SLOT_ONE);
	printf("%hu\n", save->counter++);
	jmon_save();
	while (true) {
		jmon_next_frame();
	}
}
