// .c
// Jokémon Audio
// by Kyle Furey

#include <jmon/jmon.h>

#pragma bank 0

/** Plays a note on the pulse 1 audio channel. */
static void jmon_play_pulse1(octave_t note) NONBANKED {
	if (note == NT_CONTINUE) {
		return;
	}
	if (note == NT_STOP || note >= NT_COUNT) {
		NR12_REG = 0;
		return;
	}
	ushort_t freq = rom_notes_pulse[note];
	NR12_REG = 0xF0;
	NR13_REG = freq & 0xFF;
	NR14_REG = (NR14_REG & 0xF8) | ((freq >> 8) & 0x07) | 0x80;
}

/** Plays a note on the pulse 2 audio channel. */
static void jmon_play_pulse2(octave_t note) NONBANKED {
	if (note == NT_CONTINUE) {
		return;
	}
	if (note == NT_STOP || note >= NT_COUNT) {
		NR22_REG = 0;
		return;
	}
	ushort_t freq = rom_notes_pulse[note];
	NR22_REG = 0xF0;
	NR23_REG = freq & 0xFF;
	NR24_REG = (NR24_REG & 0xF8) | ((freq >> 8) & 0x07) | 0x80;
}

/** Plays a note on the wave audio channel. */
static void jmon_play_wave(octave_t note) NONBANKED {
	if (note == NT_CONTINUE) {
		return;
	}
	if (note == NT_STOP || note >= NT_COUNT) {
		NR30_REG = 0;
		return;
	}
	ushort_t freq = rom_notes_wave[note];
	NR30_REG = 0x80;
	NR32_REG = 0x20;
	NR33_REG = freq & 0xFF;
	NR34_REG = (NR34_REG & 0xF8) | ((freq >> 8) & 0x07) | 0x80;
}

/** Plays a note on the noise audio channel. */
static void jmon_play_noise(noise_t note) NONBANKED {
	if (note == NS_CONTINUE) {
		return;
	}
	if (note == NS_STOP || note >= NS_COUNT) {
		NR42_REG = 0;
		return;
	}
	NR42_REG = 0xF0;
	NR43_REG = rom_notes_noise[note];
	NR44_REG |= 0x80;
}

/** Plays a note on each audio channel. */
static inline void jmon_play_note(octave_t pulse1, octave_t pulse2, octave_t wave, noise_t noise) NONBANKED {
	jmon_play_pulse1(pulse1);
	jmon_play_pulse2(pulse2);
	jmon_play_wave(wave);
	jmon_play_noise(noise);
}

/** Blends sound and music audio to each channel. */
static inline void jmon_blend_channels(const note_t* sound, const note_t* music) NONBANKED {
	if (sound != NULL) {
		if (music != NULL) {
			jmon_play_pulse1(sound->pulse1 != NT_STOP ? sound->pulse1 : music->pulse1);
			jmon_play_pulse2(sound->pulse2 != NT_STOP ? sound->pulse2 : music->pulse2);
			jmon_play_wave(sound->wave != NT_STOP ? sound->wave : music->wave);
			jmon_play_noise(sound->noise != NS_STOP ? sound->noise : music->noise);
		}
		else {
			jmon_play_note(sound->pulse1, sound->pulse2, sound->wave, sound->noise);
		}
	}
	else {
		if (music != NULL) {
			jmon_play_note(music->pulse1, music->pulse2, music->wave, music->noise);
		}
		else {
			jmon_play_note(NT_STOP, NT_STOP, NT_STOP, NS_STOP);
		}
	}
}

/** Cancels outgoing sound with respect to music. */
static void jmon_cancel_sound(audio_t* audio) NONBANKED {
	bool_t stop = audio->sound.track != NULL && !audio->sound.track[audio->sound.index].end;
	bool_t overlap = !audio->music.paused && audio->music.track != NULL;
	if (stop) {
		if (overlap) {
			const note_t* stopped = audio->sound.track + audio->sound.index;
			const note_t* overlapped = audio->music.track + audio->music.index;
			if (stopped->pulse1 != NT_STOP) {
				jmon_play_pulse1(overlapped->pulse1 != NT_CONTINUE ? overlapped->pulse1 : NT_STOP);
			}
			if (stopped->pulse2 != NT_STOP) {
				jmon_play_pulse2(overlapped->pulse2 != NT_CONTINUE ? overlapped->pulse2 : NT_STOP);
			}
			if (stopped->wave != NT_STOP) {
				jmon_play_wave(overlapped->wave != NT_CONTINUE ? overlapped->wave : NT_STOP);
			}
			if (stopped->noise != NS_STOP) {
				jmon_play_noise(overlapped->noise != NS_CONTINUE ? overlapped->noise : NS_STOP);
			}
		}
		else {
			jmon_play_note(NT_STOP, NT_STOP, NT_STOP, NS_STOP);
		}
	}
	else if (!overlap) {
		jmon_play_note(NT_STOP, NT_STOP, NT_STOP, NS_STOP);
	}
}

/** Cancels outgoing music with respect to sound. */
static void jmon_cancel_music(audio_t* audio) NONBANKED {
	bool_t stop = audio->music.track != NULL;
	bool_t overlap = !audio->sound.paused && audio->sound.track != NULL && !audio->sound.track[audio->sound.index].end;
	if (stop) {
		if (overlap) {
			const note_t* stopped = audio->music.track + audio->music.index;
			const note_t* overlapped = audio->sound.track + audio->sound.index;
			if (stopped->pulse1 != NT_STOP) {
				jmon_play_pulse1(overlapped->pulse1 != NT_CONTINUE ? overlapped->pulse1 : NT_STOP);
			}
			if (stopped->pulse2 != NT_STOP) {
				jmon_play_pulse2(overlapped->pulse2 != NT_CONTINUE ? overlapped->pulse2 : NT_STOP);
			}
			if (stopped->wave != NT_STOP) {
				jmon_play_wave(overlapped->wave != NT_CONTINUE ? overlapped->wave : NT_STOP);
			}
			if (stopped->noise != NS_STOP) {
				jmon_play_noise(overlapped->noise != NS_CONTINUE ? overlapped->noise : NS_STOP);
			}
		}
		else {
			jmon_play_note(NT_STOP, NT_STOP, NT_STOP, NS_STOP);
		}
	}
	else if (!overlap) {
		jmon_play_note(NT_STOP, NT_STOP, NT_STOP, NS_STOP);
	}
}

/** Plays audio over time. */
void jmon_update_audio(audio_t* audio) NONBANKED {
	if (audio == NULL) {
		return;
	}
	const note_t* sound = NULL;
	const note_t* music = NULL;
	bool_t dirty = false;
	if (!audio->sound.paused && audio->sound.track != NULL) {
		if (audio->sound.delay == 0) {
			const note_t* previous = audio->sound.track + audio->sound.index;
			if (!previous->end) {
				++audio->sound.index;
				sound = audio->sound.track + audio->sound.index;
				dirty = true;
				audio->sound.delay = sound->duration;
			}
		}
		else {
			sound = audio->sound.track + audio->sound.index;
			--audio->sound.delay;
		}
	}
	if (!audio->music.paused && audio->music.track != NULL) {
		if (audio->music.delay == 0) {
			const note_t* next = audio->music.track + audio->music.index + 1;
			if (next->end) {
				audio->music.index = 1;
			}
			else {
				++audio->music.index;
			}
			music = audio->music.track + audio->music.index;
			dirty = true;
			audio->music.delay = music->duration;
		}
		else {
			music = audio->music.track + audio->music.index;
			--audio->music.delay;
		}
	}
	if (dirty) {
		jmon_blend_channels(sound, music);
	}
}

/** Plays a one-shot sound effect from start. */
void jmon_play_sound(audio_t* audio, const note_t* sound, byte_t delay) NONBANKED {
	if (audio == NULL) {
		return;
	}
	jmon_cancel_sound(audio);
	audio->sound.paused = false;
	audio->sound.delay = delay;
	audio->sound.index = 0;
	audio->sound.track = sound;
}

/** Plays a looping music track from start. */
void jmon_play_music(audio_t* audio, const note_t* music, byte_t delay) NONBANKED {
	if (audio == NULL) {
		return;
	}
	jmon_cancel_music(audio);
	audio->music.paused = false;
	audio->music.delay = delay;
	audio->music.index = 0;
	audio->music.track = music;
}

/** Stops whatever sound effect is currently playing. */
const note_t* jmon_stop_sound(audio_t* audio) NONBANKED {
	if (audio == NULL) {
		return NULL;
	}
	const note_t* sound = audio->sound.track;
	jmon_play_sound(audio, NULL, 0);
	return sound;
}

/** Stops whatever music track is currently playing. */
const note_t* jmon_stop_music(audio_t* audio) NONBANKED {
	if (audio == NULL) {
		return NULL;
	}
	const note_t* music = audio->music.track;
	jmon_play_music(audio, NULL, 0);
	return music;
}

/** Returns whether a sound effect is currently being played. */
bool_t jmon_is_sound_playing(const audio_t* audio) NONBANKED {
	if (audio == NULL) {
		return false;
	}
	return audio->sound.track != NULL && !audio->sound.track[audio->sound.index].end;
}

/** Returns whether a music track is currently being played. */
bool_t jmon_is_music_playing(const audio_t* audio) NONBANKED {
	if (audio == NULL) {
		return false;
	}
	return audio->music.track != NULL;
}

/** Pauses whatever sound effect is currently playing. */
void jmon_pause_sound(audio_t* audio) NONBANKED {
	if (audio == NULL) {
		return;
	}
	jmon_cancel_sound(audio);
	audio->sound.paused = true;
}

/** Pauses whatever music track is currently playing. */
void jmon_pause_music(audio_t* audio) NONBANKED {
	if (audio == NULL) {
		return;
	}
	jmon_cancel_music(audio);
	audio->music.paused = true;
}

/** Unpauses whatever sound effect is currently playing. */
void jmon_unpause_sound(audio_t* audio) NONBANKED {
	if (audio == NULL) {
		return;
	}
	audio->sound.paused = false;
}

/** Unpauses whatever music track is currently playing. */
void jmon_unpause_music(audio_t* audio) NONBANKED {
	if (audio == NULL) {
		return;
	}
	audio->music.paused = false;
}

/** Returns whether a sound effect is currently paused. */
bool_t jmon_is_sound_paused(const audio_t* audio) NONBANKED {
	if (audio == NULL) {
		return false;
	}
	return audio->sound.paused;
}

/** Returns whether a music track is currently paused. */
bool_t jmon_is_music_paused(const audio_t* audio) NONBANKED {
	if (audio == NULL) {
		return false;
	}
	return audio->music.paused;
}

/** Returns a pointer to the current or last played sound effect's audio track. */
const note_t* jmon_get_sound(const audio_t* audio) NONBANKED {
	if (audio == NULL) {
		return NULL;
	}
	return audio->sound.track;
}

/** Returns a pointer to the current or last played music track's audio track. */
const note_t* jmon_get_music(const audio_t* audio) NONBANKED {
	if (audio == NULL) {
		return NULL;
	}
	return audio->music.track;
}

/** Returns the panning of an audio channel. */
panning_t jmon_get_channel_panning(audio_channel_t channel) NONBANKED {
	if (channel >= CHANNEL_COUNT) {
		return PANNING_NONE;
	}
	byte_t mask = 1 << channel;
	byte_t nr51 = NR51_REG;
	bool_t right = (nr51 & mask) != 0;
	bool_t left = (nr51 & (mask << 4)) != 0;
	if (left && right) {
		return PANNING_BOTH;
	}
	if (left) {
		return PANNING_LEFT;
	}
	if (right) {
		return PANNING_RIGHT;
	}
	return PANNING_NONE;
}

/** Sets the panning of an audio channel. */
void jmon_set_channel_panning(audio_channel_t channel, panning_t panning) NONBANKED {
	if (channel >= CHANNEL_COUNT || panning >= PANNING_COUNT) {
		return;
	}
	byte_t mask = 1 << channel;
	NR51_REG &= ~(mask | (mask << 4));
	switch (panning) {
	case PANNING_LEFT:
		NR51_REG |= mask << 4;
		break;
	case PANNING_RIGHT:
		NR51_REG |= mask;
		break;
	case PANNING_BOTH:
		NR51_REG |= mask | (mask << 4);
		break;
	default:
		break;
	}
}

/** Returns the master volume. */
volume_t jmon_get_master_volume(panning_t panning) NONBANKED {
	if (panning == PANNING_NONE || panning >= PANNING_COUNT) {
		return VOLUME_MUTED;
	}
	byte_t left = (NR50_REG >> 4) & 7;
	byte_t right = NR50_REG & 7;
	byte_t volume;
	switch (panning) {
	case PANNING_LEFT:
		volume = left;
		break;
	case PANNING_RIGHT:
		volume = right;
		break;
	default:
		volume = left < right ? left : right;
		break;
	}
	if (volume == 0) {
		return VOLUME_MUTED;
	}
	if (volume <= 2) {
		return VOLUME_LOW;
	}
	if (volume <= 5) {
		return VOLUME_HALF;
	}
	return VOLUME_FULL;
}

/** Sets the master volume. */
void jmon_set_master_volume(panning_t panning, volume_t volume) NONBANKED {
	if (panning == PANNING_NONE || panning >= PANNING_COUNT) {
		return;
	}
	byte_t value;
	switch (volume) {
	case VOLUME_MUTED:
		value = 0;
		break;
	case VOLUME_LOW:
		value = 2;
		break;
	case VOLUME_HALF:
		value = 5;
		break;
	case VOLUME_FULL:
		value = 7;
		break;
	default:
		return;
	}
	byte_t nr50 = NR50_REG;
	switch (panning) {
	case PANNING_LEFT:
		nr50 = (nr50 & 0x0F) | (value << 4);
		break;
	case PANNING_RIGHT:
		nr50 = (nr50 & 0xF0) | value;
		break;
	case PANNING_BOTH:
		nr50 = (value << 4) | value;
		break;
	default:
		return;
	}
	NR50_REG = nr50;
}
