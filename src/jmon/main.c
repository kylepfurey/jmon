// .c
// Jokémon Entry Point
// by Kyle Furey

#include <jmon/jmon.h>

#pragma bank 0

/** Music used for testing. */
const audio_track_t test_music = {
	AUDIO_START,

	AUDIO_NOTE(NT_STOP, NT_STOP, NT_STOP, NS_D, TICK_BPM(320)),
	AUDIO_NOTE(NT_STOP, NT_STOP, NT_STOP, NS_STOP, TICK_BPM(320)),
	AUDIO_NOTE(NT_STOP, NT_STOP, NT_STOP, NS_C, TICK_BPM(320)),
	AUDIO_NOTE(NT_STOP, NT_STOP, NT_STOP, NS_STOP, TICK_BPM(320)),

	AUDIO_NOTE(NT_STOP, NT_STOP, NT_STOP, NS_D, TICK_BPM(320)),
	AUDIO_NOTE(NT_STOP, NT_STOP, NT_STOP, NS_STOP, TICK_BPM(320)),
	AUDIO_NOTE(NT_STOP, NT_STOP, NT_STOP, NS_C, TICK_BPM(320)),
	AUDIO_NOTE(NT_STOP, NT_STOP, NT_STOP, NS_STOP, TICK_BPM(320)),

	AUDIO_NOTE(NT_STOP, NT_STOP, NT_STOP, NS_D, TICK_BPM(320)),
	AUDIO_NOTE(NT_STOP, NT_STOP, NT_STOP, NS_STOP, TICK_BPM(320)),
	AUDIO_NOTE(NT_STOP, NT_STOP, NT_STOP, NS_C, TICK_BPM(320)),
	AUDIO_NOTE(NT_STOP, NT_STOP, NT_STOP, NS_STOP, TICK_BPM(320)),

	AUDIO_NOTE(NT_STOP, NT_STOP, NT_STOP, NS_D, TICK_BPM(320)),
	AUDIO_NOTE(NT_STOP, NT_STOP, NT_STOP, NS_D, TICK_BPM(320)),
	AUDIO_NOTE(NT_STOP, NT_STOP, NT_STOP, NS_C, TICK_BPM(320)),
	AUDIO_NOTE(NT_STOP, NT_STOP, NT_STOP, NS_STOP, TICK_BPM(320)),

	AUDIO_END,
};

/** Sound used for testing. */
const audio_track_t test_sound = {
	AUDIO_START,

	AUDIO_NOTE(NT_7_C, NT_STOP, NT_STOP, NS_STOP, TICK_SECONDS(0.1)),
	AUDIO_NOTE(NT_7_D, NT_STOP, NT_STOP, NS_STOP, TICK_SECONDS(0.1)),
	AUDIO_NOTE(NT_7_F, NT_STOP, NT_STOP, NS_STOP, TICK_SECONDS(0.1)),
	AUDIO_NOTE(NT_7_G, NT_STOP, NT_STOP, NS_STOP, TICK_SECONDS(0.1)),

	AUDIO_END,
};

/** Game loop. */
void main(void) NONBANKED {
	jmon_init();
	input_t input = { {0} };
	audio_t audio = { {0} };
	jmon_play_sound(&audio, test_sound, TICK_SECONDS(3));
	jmon_play_music(&audio, test_music, 0);
	while (true) {
		jmon_update_input(&input);
		jmon_update_audio(&audio);
		jmon_next_frame();
	}
}
