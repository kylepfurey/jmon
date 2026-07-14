// .c
// Jokémon Saving
// by Kyle Furey

#include <jmon/jmon.h>

/** A pointer to Jokémon save data. */
#define JMON_SAVE ((volatile save_t*)0xA000)

/** A magic number used to check valid save data. */
#define JMON_MAGIC 0xBAD

#pragma bank 0

/**
 * Returns a pointer to the save data in the SRAM bank at <slot>.
 * Must be followed by a jmon_save() call.
 */
volatile save_t* jmon_load(save_slot_t slot) NONBANKED {
	ENABLE_RAM;
	SWITCH_RAM(slot % SAVE_SLOT_COUNT);
	if (JMON_SAVE->magic != JMON_MAGIC) {
		memset(JMON_SAVE, 0, sizeof(save_t));
	}
	return JMON_SAVE;
}

/** Closes the SRAM bank loaded with jmon_load(). */
void jmon_save(void) NONBANKED {
	ENABLE_RAM;
	JMON_SAVE->magic = JMON_MAGIC;
	SWITCH_RAM(0);
	DISABLE_RAM;
}

/**
 * Returns whether save data exists in the SRAM bank at <slot>.
 * This should never be called between jmon_load() and jmon_save().
 */
bool_t jmon_has_save(save_slot_t slot) NONBANKED {
	ENABLE_RAM;
	SWITCH_RAM(slot % SAVE_SLOT_COUNT);
	bool_t result = JMON_SAVE->magic == JMON_MAGIC;
	SWITCH_RAM(0);
	DISABLE_RAM;
	return result;
}

/**
 * Deletes save data in the SRAM bank at <slot>.
 * This should never be called between jmon_load() and jmon_save().
 */
void jmon_delete_save(save_slot_t slot) NONBANKED {
	ENABLE_RAM;
	SWITCH_RAM(slot % SAVE_SLOT_COUNT);
	memset(JMON_SAVE, 0, sizeof(save_t));
	SWITCH_RAM(0);
	DISABLE_RAM;
}
