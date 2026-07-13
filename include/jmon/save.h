// .h
// Jokémon Saving
// by Kyle Furey

#pragma once
#include <jmon/types.h>

/** Each valid saving slot index and the total number of slots. */
typedef enum {
	SAVE_SLOT_ONE = 0,
	SAVE_SLOT_TWO = 1,
	SAVE_SLOT_THREE = 2,
	SAVE_SLOT_FOUR = 3,
	SAVE_SLOT_COUNT,
} save_slot_t;

/** Jokémon save data. */
typedef struct {
	/** A magic number used to check valid save data. */
	ushort_t magic;

	/** For testing. */
	byte_t counter;
} save_t;

/**
 * Returns a pointer to the save data in the SRAM bank at <slot>.
 * Must be followed by a jmon_save() call.
 */
JMON_FUNC volatile save_t* jmon_load(save_slot_t slot) NONBANKED;

/** Closes the SRAM bank loaded with jmon_load(). */
JMON_FUNC void jmon_save(void) NONBANKED;

/**
 * Returns whether save data exists in the SRAM bank at <slot>.
 * This should never be called between jmon_load() and jmon_save().
 */
JMON_FUNC bool_t jmon_has_save(save_slot_t slot) NONBANKED;

/**
 * Deletes save data in the SRAM bank at <slot>.
 * This should never be called between jmon_load() and jmon_save().
 */
JMON_FUNC void jmon_delete_save(save_slot_t slot) NONBANKED;
