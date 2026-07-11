// .h
// Jokémon Rendering
// by Kyle Furey

#pragma once
#include <jmon/types.h>

/** Initializes rendering. */
JMON_FUNC void jmon_init(void) NONBANKED;

/** Advances to the next frame. */
JMON_FUNC void jmon_next_frame(void) NONBANKED;
