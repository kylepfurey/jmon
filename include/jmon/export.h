// .h
// Jokémon Export Macros
// by Kyle Furey

#pragma once

/**
 * Jokémon inline function specifiers.
 * This function does not reserve a bank, or is set to bank BANK_STATIC.
 */
#define JMON_INLINE inline

/**
 * Jokémon banked function specifiers.
 * <bank> is the ROM bank this function lives in.
 */
#define JMON_FUNC(bank) extern

/**
 * Jokémon banked data specifiers.
 * <bank> is the ROM bank this data lives in.
 */
#define JMON_DATA(bank) extern const

/** Static ROM bank. Always loaded. */
#define BANK_STATIC 0
