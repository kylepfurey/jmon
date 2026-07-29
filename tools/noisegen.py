# .py
# GameBoy Audio Noise Frequencies Generator
# by Claude

#!/usr/bin/env python3
"""
Generate a 12-value noise "scale" (NR43 register values) and repeat it
across every octave block, since the noise channel's LFSR only supports
a limited, non-continuous set of frequencies (not true musical octaves).
"""

import math

NOTE_NAMES = ["C", "CS", "D", "DS", "E", "F", "FS", "G", "GS", "A", "AS", "B"]
DIVISOR_RATIOS = [8, 16, 32, 48, 64, 80, 96, 112]

def noise_freq(shift: int, divisor_code: int) -> float:
    return 524288 / DIVISOR_RATIOS[divisor_code] / (2 ** (shift + 1))

def all_noise_registers(width_mode: int = 0):
    """Return sorted (freq, nr43) pairs, deduplicated by frequency."""
    seen = {}
    for shift in range(16):
        for dcode in range(8):
            freq = noise_freq(shift, dcode)
            nr43 = (shift << 4) | (width_mode << 3) | dcode
            key = round(freq, 3)
            if key not in seen:
                seen[key] = nr43
    return sorted((freq, nr43) for freq, nr43 in seen.items())

def pick_scale(n=12, min_freq=120, max_freq=6000, width_mode=0):
    """Pick n log-spaced noise frequencies from the achievable set."""
    registers = all_noise_registers(width_mode)
    in_range = [(f, nr) for f, nr in registers if min_freq <= f <= max_freq]

    if len(in_range) < n:
        raise ValueError(
            f"Only {len(in_range)} distinct noise frequencies available "
            f"in [{min_freq}, {max_freq}] Hz — widen the range or reduce n."
        )

    log_min, log_max = math.log(min_freq), math.log(max_freq)
    targets = [
        math.exp(log_min + (log_max - log_min) * i / (n - 1))
        for i in range(n)
    ]

    scale = []
    used = set()
    for t in targets:
        # pick closest unused frequency to avoid duplicate scale steps
        candidates = [fr for fr in in_range if fr[1] not in used]
        best = min(candidates, key=lambda fr: abs(fr[0] - t))
        scale.append(best)
        used.add(best[1])
    return scale

def format_c_array(entries, per_line=12):
    lines = []
    for i in range(0, len(entries), per_line):
        row = entries[i:i + per_line]
        row_str = ",".join(f"[{label}]={val}" for label, val in row)
        lines.append("\t" + row_str + ",")
    return "\n".join(lines)

def main():
    octaves = list(range(2, 9))  # 7 octave blocks: NT_2_.. through NT_8_..

    scale = pick_scale(n=12, min_freq=120, max_freq=6000, width_mode=0)
    nr43_values = [nr43 for _freq, nr43 in scale]

    labels = [f"NT_{octave}_{name}" for octave in octaves for name in NOTE_NAMES]
    full_values = nr43_values * len(octaves)  # repeat the 12-step scale per octave

    entries = list(zip(labels, full_values))

    print("/** Precomputed note values for the noise audio channel. */")
    print("const ushort_t rom_notes_noise[NT_COUNT] = {")
    print(format_c_array(entries))
    print("};\n")

    input()

if __name__ == "__main__":
    main()
