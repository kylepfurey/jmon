// .h
// Jokémon Input
// by Kyle Furey

#pragma once
#include <jmon/types.h>

/** Each valid input action. */
typedef enum {
	IA_UP = J_UP,
	IA_RIGHT = J_RIGHT,
	IA_DOWN = J_DOWN,
	IA_LEFT = J_LEFT,
	IA_B = J_B,
	IA_A = J_A,
	IA_SELECT = J_SELECT,
	IA_START = J_START,
	IA_ANY = 255,
} input_actions_t;

/** The state of Jokémon user input. */
typedef struct {
	/** Is input disabled? */
	bool_t disabled;

	/** Previous user input. */
	input_actions_t previous;

	/** Current user input. */
	input_actions_t current;
} input_t;

/** Refreshes the current user input. */
JMON_FUNC void jmon_update_input(input_t* input) NONBANKED;

/** Enables input for Jokémon. */
JMON_FUNC void jmon_enable_input(input_t* input) NONBANKED;

/** Disables input for Jokémon. */
JMON_FUNC void jmon_disable_input(input_t* input) NONBANKED;

/** Returns whether input is currently enabled. */
JMON_FUNC bool_t jmon_is_input_enabled(const input_t* input) NONBANKED;

/** Returns whether input actions were pressed this frame. */
JMON_FUNC bool_t jmon_is_input_pressed(const input_t* input, input_actions_t actions) NONBANKED;

/** Returns whether input actions were pressed this and last frame. */
JMON_FUNC bool_t jmon_is_input_held(const input_t* input, input_actions_t actions) NONBANKED;

/** Returns whether input actions were pressed last frame but not this frame. */
JMON_FUNC bool_t jmon_is_input_released(const input_t* input, input_actions_t actions) NONBANKED;

/** Blocks until specific input actions are pressed. */
JMON_FUNC void jmon_await_input_pressed(input_t* input, input_actions_t actions) NONBANKED;

/** Blocks until specific input actions are released. */
JMON_FUNC void jmon_await_input_released(input_t* input, input_actions_t actions) NONBANKED;

/** Converts an input action into a string. */
JMON_FUNC string_t jmon_input_to_string(input_actions_t action) BANKED;
