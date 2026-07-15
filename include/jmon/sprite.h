// .h
// Jokémon Sprites
// by Kyle Furey

#pragma once
#include <jmon/types.h>

/** Returns the number of sprite tiles in a sprite. */
#define SPRITE_TILES(rom_sprite) (sizeof((rom_sprite)) / 16)

/** One or more 8 x 8 sprite tiles. */
typedef const byte_t sprite_t[];

/** A null-terminated array of metasprite pointers that can be animated in order. */
typedef const metasprite_t* const animation_t[];
