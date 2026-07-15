// .h
// Jokémon Audio
// by Kyle Furey

#pragma once
#include <jmon/types.h>

/** Constructs a note for an audio track. */
#define AUDIO_NOTE(pulse, wave, noise, duration) {(pulse), (wave), (noise), (duration)}

/** A note used to signal the end of an audio track. */
#define AUDIO_END AUDIO_NOTE(255, 255, 255, 255)

/** Each channel type and the total number of channels. */
typedef enum {
	CHANNEL_PULSE_ONE = 0,
	CHANNEL_PULSE_TWO = 1,
	CHANNEL_WAVE = 2,
	CHANNEL_NOISE = 3,
	CHANNEL_COUNT,
} audio_channel_t;

/** Data for a single note to be played in audio. */
typedef struct {
	/** The index of the note to play for the pulse channel. */
	byte_t pulse;

	/** The index of the note to play for the wave channel. */
	byte_t wave;

	/** The index of the note to play for the noise channel. */
	byte_t noise;

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
	 * Channels shared by sounds and music will be used by sounds first.
	 * This audio track internally uses CHANNEL_PULSE_ONE for pulse notes.
	 */
	audio_player_t sound;

	/**
	 * The audio player for the current looping music being played.
	 * Channels shared by sounds and music will be used by sounds first.
	 * This audio track internally uses CHANNEL_PULSE_TWO for pulse notes.
	 */
	audio_player_t music;
} audio_t;

/** Plays audio over time. */
JMON_FUNC void jmon_update_audio(audio_t* audio) NONBANKED;
