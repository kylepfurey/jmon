// .h
// Jokémon Color
// by Kyle Furey

#pragma once
#include <jmon/types.h>

/**
 * A color palette of 4 colors.
 * For tiles, index 0 is a valid color.
 * For sprites, index 0 is always transparent.
 */
typedef const palette_color_t palette_t[4];

/** Is Jokémon running on GameBoy Color? */
JMON_FUNC bool_t jmon_is_gbc(void) NONBANKED;
