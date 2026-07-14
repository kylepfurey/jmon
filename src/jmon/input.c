// .c
// Jokémon Input
// by Kyle Furey

#include <jmon/jmon.h>

#pragma bank 0

/** Refreshes the current user input. */
void jmon_update_input(input_t* input) NONBANKED {
	if (input == NULL) {
		return;
	}
	input->previous = input->current;
	input->current = input->disabled ? 0 : joypad();
}

/** Returns whether input is currently enabled. */
bool_t jmon_is_input_enabled(const input_t* input) NONBANKED {
	if (input == NULL) {
		return false;
	}
	return !input->disabled;
}

/** Enables input for Jokémon. */
void jmon_enable_input(input_t* input) NONBANKED {
	if (input == NULL) {
		return;
	}
	input->disabled = false;
}

/** Disables input for Jokémon. */
void jmon_disable_input(input_t* input) NONBANKED {
	if (input == NULL) {
		return;
	}
	input->disabled = true;
}

/** Returns whether input actions were pressed this frame. */
bool_t jmon_is_input_pressed(const input_t* input, input_actions_t actions) NONBANKED {
	if (input == NULL || actions == 0) {
		return false;
	}
	if (actions == IA_ANY) {
		return input->previous == 0 && input->current != 0;
	}
	return (input->previous & actions) == 0 && (input->current & actions) != 0;
}

/** Returns whether input actions were pressed this and last frame. */
bool_t jmon_is_input_held(const input_t* input, input_actions_t actions) NONBANKED {
	if (input == NULL || actions == 0) {
		return false;
	}
	if (actions == IA_ANY) {
		return input->previous != 0 && input->current != 0;
	}
	return (input->previous & actions) != 0 && (input->current & actions) != 0;
}

/** Returns whether input actions were pressed last frame but not this frame. */
bool_t jmon_is_input_released(const input_t* input, input_actions_t actions) NONBANKED {
	if (input == NULL || actions == 0) {
		return false;
	}
	if (actions == IA_ANY) {
		return input->previous != 0 && input->current == 0;
	}
	return (input->previous & actions) != 0 && (input->current & actions) == 0;
}

/** Blocks until specific input actions are pressed. */
void jmon_await_input_pressed(input_t* input, input_actions_t actions) NONBANKED {
	if (input == NULL || actions == 0) {
		return;
	}
	jmon_update_input(input);
	while (!jmon_is_input_pressed(input, actions)) {
		vsync();
		jmon_update_input(input);
	}
}

/** Blocks until specific input actions are released. */
void jmon_await_input_released(input_t* input, input_actions_t actions) NONBANKED {
	if (input == NULL || actions == 0) {
		return;
	}
	jmon_update_input(input);
	while (!jmon_is_input_released(input, actions)) {
		vsync();
		jmon_update_input(input);
	}
}
