// .c
// Jokémon Read-only Audio
// by Kyle Furey

#include <jmon/jmon.h>

#pragma bank 0

/** Each precomputed note value. */
BANKREF(notes)

/** Precomputed note values for the pulse audio channel. */
const ushort_t rom_notes_pulse[NT_COUNT] = {
    [NT_2_C]=44,[NT_2_CS]=157,[NT_2_D]=263,[NT_2_DS]=363,[NT_2_E]=457,[NT_2_F]=547,[NT_2_FS]=631,[NT_2_G]=711,[NT_2_GS]=786,[NT_2_A]=856,[NT_2_AS]=923,[NT_2_B]=986,
    [NT_3_C]=1046,[NT_3_CS]=1102,[NT_3_D]=1155,[NT_3_DS]=1205,[NT_3_E]=1253,[NT_3_F]=1297,[NT_3_FS]=1339,[NT_3_G]=1379,[NT_3_GS]=1417,[NT_3_A]=1452,[NT_3_AS]=1486,[NT_3_B]=1517,
    [NT_4_C]=1547,[NT_4_CS]=1575,[NT_4_D]=1602,[NT_4_DS]=1627,[NT_4_E]=1650,[NT_4_F]=1673,[NT_4_FS]=1694,[NT_4_G]=1714,[NT_4_GS]=1732,[NT_4_A]=1750,[NT_4_AS]=1767,[NT_4_B]=1783,
    [NT_5_C]=1798,[NT_5_CS]=1812,[NT_5_D]=1825,[NT_5_DS]=1837,[NT_5_E]=1849,[NT_5_F]=1860,[NT_5_FS]=1871,[NT_5_G]=1881,[NT_5_GS]=1890,[NT_5_A]=1899,[NT_5_AS]=1907,[NT_5_B]=1915,
    [NT_6_C]=1923,[NT_6_CS]=1930,[NT_6_D]=1936,[NT_6_DS]=1943,[NT_6_E]=1949,[NT_6_F]=1954,[NT_6_FS]=1959,[NT_6_G]=1964,[NT_6_GS]=1969,[NT_6_A]=1974,[NT_6_AS]=1978,[NT_6_B]=1982,
    [NT_7_C]=1985,[NT_7_CS]=1989,[NT_7_D]=1992,[NT_7_DS]=1995,[NT_7_E]=1998,[NT_7_F]=2001,[NT_7_FS]=2004,[NT_7_G]=2006,[NT_7_GS]=2009,[NT_7_A]=2011,[NT_7_AS]=2013,[NT_7_B]=2015,
    [NT_8_C]=2017,[NT_8_CS]=2018,[NT_8_D]=2020,[NT_8_DS]=2022,[NT_8_E]=2023,[NT_8_F]=2025,[NT_8_FS]=2026,[NT_8_G]=2027,[NT_8_GS]=2028,[NT_8_A]=2029,[NT_8_AS]=2030,[NT_8_B]=2031,
};

/** Precomputed note values for the wave audio channel. */
const ushort_t rom_notes_wave[NT_COUNT] = {
    [NT_2_C]=44,[NT_2_CS]=157,[NT_2_D]=263,[NT_2_DS]=363,[NT_2_E]=457,[NT_2_F]=547,[NT_2_FS]=631,[NT_2_G]=711,[NT_2_GS]=786,[NT_2_A]=856,[NT_2_AS]=923,[NT_2_B]=986,
    [NT_3_C]=1046,[NT_3_CS]=1102,[NT_3_D]=1155,[NT_3_DS]=1205,[NT_3_E]=1253,[NT_3_F]=1297,[NT_3_FS]=1339,[NT_3_G]=1379,[NT_3_GS]=1417,[NT_3_A]=1452,[NT_3_AS]=1486,[NT_3_B]=1517,
    [NT_4_C]=1547,[NT_4_CS]=1575,[NT_4_D]=1602,[NT_4_DS]=1627,[NT_4_E]=1650,[NT_4_F]=1673,[NT_4_FS]=1694,[NT_4_G]=1714,[NT_4_GS]=1732,[NT_4_A]=1750,[NT_4_AS]=1767,[NT_4_B]=1783,
    [NT_5_C]=1798,[NT_5_CS]=1812,[NT_5_D]=1825,[NT_5_DS]=1837,[NT_5_E]=1849,[NT_5_F]=1860,[NT_5_FS]=1871,[NT_5_G]=1881,[NT_5_GS]=1890,[NT_5_A]=1899,[NT_5_AS]=1907,[NT_5_B]=1915,
    [NT_6_C]=1923,[NT_6_CS]=1930,[NT_6_D]=1936,[NT_6_DS]=1943,[NT_6_E]=1949,[NT_6_F]=1954,[NT_6_FS]=1959,[NT_6_G]=1964,[NT_6_GS]=1969,[NT_6_A]=1974,[NT_6_AS]=1978,[NT_6_B]=1982,
    [NT_7_C]=1985,[NT_7_CS]=1989,[NT_7_D]=1992,[NT_7_DS]=1995,[NT_7_E]=1998,[NT_7_F]=2001,[NT_7_FS]=2004,[NT_7_G]=2006,[NT_7_GS]=2009,[NT_7_A]=2011,[NT_7_AS]=2013,[NT_7_B]=2015,
    [NT_8_C]=2017,[NT_8_CS]=2018,[NT_8_D]=2020,[NT_8_DS]=2022,[NT_8_E]=2023,[NT_8_F]=2025,[NT_8_FS]=2026,[NT_8_G]=2027,[NT_8_GS]=2028,[NT_8_A]=2029,[NT_8_AS]=2030,[NT_8_B]=2031,
};

/** Precomputed note values for the noise audio channel. */
const ushort_t rom_notes_noise[NS_COUNT] = {
    [NS_C]=84,[NS_CS]=70,[NS_D]=68,[NS_DS]=54,[NS_E]=52,[NS_F]=38,[NS_FS]=36,[NS_G]=22,[NS_GS]=20,[NS_A]=6,[NS_AS]=4,[NS_B]=3,
};
