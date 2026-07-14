// .c
// Jokémon Read-only Strings
// by Kyle Furey

#include <jmon/jmon.h>

#pragma bank 1

/** Contains each input string. */
BANKREF(input_strings)

/** String for no input. */
const string_t rom_string_input_none = "NONE";

/** String for up input. */
const string_t rom_string_input_up = "UP";

/** String for right input. */
const string_t rom_string_input_right = "RIGHT";

/** String for down input. */
const string_t rom_string_input_down = "DOWN";

/** String for left input. */
const string_t rom_string_input_left = "LEFT";

/** String for B input. */
const string_t rom_string_input_b = "B";

/** String for A input. */
const string_t rom_string_input_a = "A";

/** String for select input. */
const string_t rom_string_input_select = "SELECT";

/** String for start input. */
const string_t rom_string_input_start = "START";

/** Converts an input action into a string. */
string_t jmon_input_to_string(input_actions_t action) BANKED {
	switch (action) {
	case IA_UP:
		return rom_string_input_up;
	case IA_RIGHT:
		return rom_string_input_right;
	case IA_DOWN:
		return rom_string_input_down;
	case IA_LEFT:
		return rom_string_input_left;
	case IA_B:
		return rom_string_input_b;
	case IA_A:
		return rom_string_input_a;
	case IA_SELECT:
		return rom_string_input_select;
	case IA_START:
		return rom_string_input_start;
	default:
		return rom_string_input_none;
	}
}
