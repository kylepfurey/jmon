// .h
// Jokémon Read-only Strings
// by Kyle Furey

#pragma once
#include <jmon/types.h>

/** Contains each input string. */
BANKREF_EXTERN(input_strings)

/** String for no input. */
JMON_DATA string_t rom_string_input_none;

/** String for up input. */
JMON_DATA string_t rom_string_input_up;

/** String for right input. */
JMON_DATA string_t rom_string_input_right;

/** String for down input. */
JMON_DATA string_t rom_string_input_down;

/** String for left input. */
JMON_DATA string_t rom_string_input_left;

/** String for B input. */
JMON_DATA string_t rom_string_input_b;

/** String for A input. */
JMON_DATA string_t rom_string_input_a;

/** String for select input. */
JMON_DATA string_t rom_string_input_select;

/** String for start input. */
JMON_DATA string_t rom_string_input_start;
