// .h
// Jokémon Sprites
// by Kyle Furey

#pragma once
#include <jmon/types.h>

/** One or more 8 x 8 sprite tiles. */
typedef byte_t tile_t[];

/** A collection of sprite tiles that create a single metasprite. */
typedef metasprite_t sprite_t[];

/** A collection of metasprites that can be animated in order. */
typedef sprite_t *animation_t[];
