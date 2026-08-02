// .h
// Jokémon Sprites
// by Kyle Furey

#pragma once
#include <jmon/types.h>

/** The last index of the tile map array. */
#define TILE_COUNT 32

/** Returns the number of sprite tiles in a sprite. */
#define SPRITE_TILES(rom_sprite) (sizeof((rom_sprite)) / 16)

/** One or more 8 x 8 sprite tiles. */
typedef const byte_t sprite_t[];

/** A null-terminated array of metasprite pointers that can be animated in order. */
typedef const metasprite_t* const animation_t[];

/** Loads one or more sprite tiles into background VRAM. */
JMON_FUNC void jmon_load_background_tiles(byte_t index, const byte_t* tiles, byte_t count) NONBANKED;

/** Loads one or more sprite tiles into object VRAM. */
JMON_FUNC void jmon_load_object_tiles(byte_t index, const byte_t* tiles, byte_t count) NONBANKED;
