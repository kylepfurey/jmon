// .c
// Jokémon Entry Point
// by Kyle Furey

#include <jmon/jmon.h>

#pragma bank 0

/** Music used for testing. */
audio_track_t test_song = {
	AUDIO_START,

	AUDIO_NOTE(NT_4_C, NT_6_C, NT_STOP, NS_STOP, TICK_BPM(120)),
	AUDIO_NOTE(NT_4_D, NT_6_D, NT_STOP, NS_STOP, TICK_BPM(120)),
	AUDIO_NOTE(NT_4_E, NT_6_E, NT_STOP, NS_STOP, TICK_BPM(120)),
	AUDIO_NOTE(NT_4_F, NT_6_F, NT_STOP, NS_STOP, TICK_BPM(120)),
	AUDIO_NOTE(NT_4_G, NT_6_G, NT_STOP, NS_STOP, TICK_BPM(120)),
	AUDIO_NOTE(NT_4_A, NT_6_A, NT_STOP, NS_STOP, TICK_BPM(120)),
	AUDIO_NOTE(NT_4_B, NT_6_B, NT_STOP, NS_STOP, TICK_BPM(120)),
	AUDIO_NOTE(NT_5_C, NT_7_C, NT_STOP, NS_STOP, TICK_BPM(120)),

	AUDIO_NOTE(NT_5_C, NT_7_C, NT_6_C,  NS_C,    TICK_SECONDS(1)),

	AUDIO_NOTE(NT_4_B, NT_6_B, NT_STOP, NS_STOP, TICK_BPM(120)),
	AUDIO_NOTE(NT_4_A, NT_6_A, NT_STOP, NS_STOP, TICK_BPM(120)),
	AUDIO_NOTE(NT_4_G, NT_6_G, NT_STOP, NS_STOP, TICK_BPM(120)),
	AUDIO_NOTE(NT_4_F, NT_6_F, NT_STOP, NS_STOP, TICK_BPM(120)),
	AUDIO_NOTE(NT_4_E, NT_6_E, NT_STOP, NS_STOP, TICK_BPM(120)),
	AUDIO_NOTE(NT_4_D, NT_6_D, NT_STOP, NS_STOP, TICK_BPM(120)),

	AUDIO_NOTE(NT_4_C, NT_6_C, NT_3_C,  NS_C,    TICK_SECONDS(1)),

	AUDIO_END,
};

/** Game loop. */
void main(void) NONBANKED {
	jmon_init();
	input_t input = { {0} };
	audio_t audio = { {0} };
	jmon_play_music(&audio, test_song, 0);
	while (true) {
		jmon_update_input(&input);
		jmon_update_audio(&audio);
		jmon_next_frame();
	}
}
