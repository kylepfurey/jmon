// .h
// Jokémon Color
// by Kyle Furey

#pragma once
#include <jmon/types.h>

/** The last index of the VRAM palette array. */
#define PALETTE_COUNT 8

/**
 * A color palette of 4 colors.
 * For UI, index 0 is a valid color.
 * For objects, index 0 is always transparent.
 */
typedef const palette_color_t palette_t[4];

/** Is Jokémon running on GameBoy Color? */
JMON_FUNC bool_t jmon_is_gbc(void) NONBANKED;

/** Loads one or more palettes into background VRAM. */
JMON_FUNC void jmon_load_background_palettes(byte_t index, const palette_color_t* palettes, byte_t count) NONBANKED;

/** Loads one or more palettes into object VRAM. */
JMON_FUNC void jmon_load_object_palettes(byte_t index, const palette_color_t* palettes, byte_t count) NONBANKED;
