// .h
// Jokémon Audio
// by Kyle Furey

#pragma once
#include <jmon/types.h>

/** Constructs a note for an audio track. */
#define AUDIO_NOTE(pulse, wave, noise, duration) {(pulse), (wave), (noise), (duration)}

/** A note used to signal the end of an audio track. */
#define AUDIO_END AUDIO_NOTE(NT_STOP, NT_STOP, NT_STOP, NT_STOP)

/** Each audio channel type and the total number of audio channels. */
typedef enum {
	CHANNEL_PULSE_ONE = 0,
	CHANNEL_PULSE_TWO = 1,
	CHANNEL_WAVE = 2,
	CHANNEL_NOISE = 3,
	CHANNEL_COUNT,
} audio_channel_t;

/** Each available volume level for audio channels. */
typedef enum {
	VOLUME_MUTED = 0,
	VOLUME_LOW = 1,
	VOLUME_HALF = 2,
	VOLUME_FULL = 3,
	VOLUME_COUNT,
} audio_volume_t;

/** Each octave and note that can be played on an audio channel. */
typedef enum {
	//   C       C#       D       D#       E       F       F#       G       G#       A       A#       B
	NT_2_C, NT_2_CS, NT_2_D, NT_2_DS, NT_2_E, NT_2_F, NT_2_FS, NT_2_G, NT_2_GS, NT_2_A, NT_2_AS, NT_2_B, // Octave 2
	NT_3_C, NT_3_CS, NT_3_D, NT_3_DS, NT_3_E, NT_3_F, NT_3_FS, NT_3_G, NT_3_GS, NT_3_A, NT_3_AS, NT_3_B, // Octave 3
	NT_4_C, NT_4_CS, NT_4_D, NT_4_DS, NT_4_E, NT_4_F, NT_4_FS, NT_4_G, NT_4_GS, NT_4_A, NT_4_AS, NT_4_B, // Octave 4
	NT_5_C, NT_5_CS, NT_5_D, NT_5_DS, NT_5_E, NT_5_F, NT_5_FS, NT_5_G, NT_5_GS, NT_5_A, NT_5_AS, NT_5_B, // Octave 5
	NT_6_C, NT_6_CS, NT_6_D, NT_6_DS, NT_6_E, NT_6_F, NT_6_FS, NT_6_G, NT_6_GS, NT_6_A, NT_6_AS, NT_6_B, // Octave 6
	NT_7_C, NT_7_CS, NT_7_D, NT_7_DS, NT_7_E, NT_7_F, NT_7_FS, NT_7_G, NT_7_GS, NT_7_A, NT_7_AS, NT_7_B, // Octave 7
	NT_8_C, NT_8_CS, NT_8_D, NT_8_DS, NT_8_E, NT_8_F, NT_8_FS, NT_8_G, NT_8_GS, NT_8_A, NT_8_AS, NT_8_B, // Octave 8
	NT_COUNT,
	NT_CONTINUE = 254,
	NT_STOP = 255,
} octave_t;

/** Data for when and what note is playing per audio channel in an audio track. */
typedef struct {
	/** The note to play for the pulse audio channel. */
	octave_t pulse;

	/** The note to play for the wave audio channel. */
	octave_t wave;

	/** The note to play for the noise audio channel. */
	octave_t noise;

	/** The duration to play the note for. */
	byte_t duration;
} note_t;

/** A terminated array of notes that form a playable audio track for sounds and music. */
typedef const note_t audio_track_t[];

/** Data for playing an audio track. */
typedef struct {
	/** Is this audio player paused? */
	bool_t paused;

	/** The delay in ticks before playing the next note. */
	byte_t delay;

	/** The index of the current note. */
	ushort_t index;

	/** A pointer to the audio track being played. */
	const audio_track_t* track;
} audio_player_t;

/** The state of Jokémon audio. */
typedef struct {
	/**
	 * The audio player for the current one-shot sound being played.
	 * Audio channels shared by sounds and music will be used by sounds first.
	 * This audio track internally uses CHANNEL_PULSE_ONE for pulse notes.
	 */
	audio_player_t sound;

	/**
	 * The audio player for the current looping music being played.
	 * Audio channels shared by sounds and music will be used by sounds first.
	 * This audio track internally uses CHANNEL_PULSE_TWO for pulse notes.
	 */
	audio_player_t music;
} audio_t;

/** Plays audio over time. */
JMON_FUNC void jmon_update_audio(audio_t* audio) NONBANKED;

/** Plays a one-shot sound effect from start. */
JMON_FUNC void jmon_play_sound(audio_t* audio, const audio_track_t* sound) NONBANKED;

/** Plays a looping music track from start. */
JMON_FUNC void jmon_play_music(audio_t* audio, const audio_track_t* music) NONBANKED;

/** Stops whatever sound effect is currently playing. */
JMON_FUNC void jmon_stop_sound(audio_t* audio) NONBANKED;

/** Stops whatever music track is currently playing. */
JMON_FUNC void jmon_stop_music(audio_t* audio) NONBANKED;

/** Returns whether a sound effect is currently being played. */
JMON_FUNC bool_t jmon_is_sound_playing(const audio_t* audio) NONBANKED;

/** Returns whether a music track is currently being played. */
JMON_FUNC bool_t jmon_is_music_playing(const audio_t* audio) NONBANKED;

/** Pauses whatever sound effect is currently playing. */
JMON_FUNC void jmon_pause_sound(audio_t* audio) NONBANKED;

/** Pauses whatever music track is currently playing. */
JMON_FUNC void jmon_pause_music(audio_t* audio) NONBANKED;

/** Unpauses whatever sound effect is currently playing. */
JMON_FUNC void jmon_unpause_sound(audio_t* audio) NONBANKED;

/** Unpauses whatever music track is currently playing. */
JMON_FUNC void jmon_unpause_music(audio_t* audio) NONBANKED;

/** Returns whether a sound effect is currently paused. */
JMON_FUNC bool_t jmon_is_sound_paused(const audio_t* audio) NONBANKED;

/** Returns whether a music track is currently paused. */
JMON_FUNC bool_t jmon_is_music_paused(const audio_t* audio) NONBANKED;

/** Returns a pointer to the current or last played sound effect's audio track. */
JMON_FUNC const audio_track_t* jmon_get_sound(const audio_t* audio) NONBANKED;

/** Returns a pointer to the current or last played music track's audio track. */
JMON_FUNC const audio_track_t* jmon_get_music(const audio_t* audio) NONBANKED;

/** Returns the volume of an audio channel. */
JMON_FUNC audio_volume_t jmon_get_channel_volume(audio_channel_t channel) NONBANKED;

/** Sets the volume of an audio channel. */
JMON_FUNC void jmon_set_channel_volume(audio_channel_t channel, audio_volume_t volume) NONBANKED;

/** Returns the master volume. */
JMON_FUNC audio_volume_t jmon_get_master_volume(void) NONBANKED;

/** Sets the master volume. */
JMON_FUNC void jmon_set_master_volume(audio_volume_t volume) NONBANKED;
