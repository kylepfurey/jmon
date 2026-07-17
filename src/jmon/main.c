// .c
// Jokémon Entry Point
// by Kyle Furey

#include <jmon/jmon.h>

#pragma bank 0

/** Game loop. */
void main(void) NONBANKED {
	jmon_init();
	printf(jmon_has_save(SAVE_SLOT_ONE) ? "SAVE FOUND" : "NO SAVE");
	jmon_save();
	input_t input = { {0} };
	audio_t audio = { {0} };
	while (true) {
		jmon_update_input(&input);
		jmon_update_audio(&audio);
		jmon_next_frame();
	}
}
