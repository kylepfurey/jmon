// .h
// Jokémon Read-only Audio
// by Kyle Furey

#pragma once
#include <jmon/audio.h>

/** Each precomputed note value. */
BANKREF_EXTERN(notes)

/** Precomputed note values for the pulse audio channel. */
JMON_DATA ushort_t rom_notes_pulse[NT_COUNT];

/** Precomputed note values for the wave audio channel. */
JMON_DATA ushort_t rom_notes_wave[NT_COUNT];

/** Precomputed note values for the noise audio channel. */
JMON_DATA ushort_t rom_notes_noise[NT_COUNT];
