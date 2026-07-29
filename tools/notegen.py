# .py
# GameBoy Audio Note Frequencies Generator
# by Claude

#!/usr/bin/env python3
"""
Generate precomputed Game Boy frequency register values
(pulse and wave channels) for notes C2..B8.

Pulse: freq = 131072 / (2048 - x)  =>  x = 2048 - round(131072 / freq)
Wave:  freq = 65536  / (2048 - x)  =>  x = 2048 - round(65536  / freq)
"""

import math

NOTE_NAMES = ["C", "CS", "D", "DS", "E", "F", "FS", "G", "GS", "A", "AS", "B"]

A4_FREQ = 440.0
A4_MIDI = 69  # MIDI note number for A4

def note_frequency(octave: int, semitone_index: int) -> float:
    """
    octave: scientific pitch notation octave number (C2..B8 here)
    semitone_index: 0=C, 1=C#, ... 11=B
    """
    # MIDI note number: C-1 = 0, so C(octave) = (octave + 1) * 12
    midi_note = (octave + 1) * 12 + semitone_index
    return A4_FREQ * (2 ** ((midi_note - A4_MIDI) / 12.0))

def freq_to_pulse_reg(freq_hz: float) -> int:
    x = 2048 - round(131072 / freq_hz)
    return max(0, min(2047, x))

def freq_to_wave_reg(freq_hz: float) -> int:
    x = 2048 - round(65536 / freq_hz)
    return max(0, min(2047, x))

def generate_table(octaves, reg_func):
    entries = []
    for octave in octaves:
        for semitone_index, name in enumerate(NOTE_NAMES):
            freq = note_frequency(octave, semitone_index)
            reg_val = reg_func(freq)
            label = f"NT_{octave}_{name}"
            entries.append((label, reg_val, freq))
    return entries

def format_c_array(entries, per_line=12):
    lines = []
    for i in range(0, len(entries), per_line):
        row = entries[i:i + per_line]
        row_str = ",".join(f"[{label}]={val}" for label, val, _ in row)
        lines.append("\t" + row_str + ",")
    return "\n".join(lines)

def main():
    octaves = range(2, 9)  # C2..B8

    pulse_entries = generate_table(octaves, freq_to_pulse_reg)
    wave_entries = generate_table(octaves, freq_to_wave_reg)

    print("/** Precomputed note values for the pulse audio channel. */")
    print("const ushort_t rom_notes_pulse[NT_COUNT] = {")
    print(format_c_array(pulse_entries))
    print("};\n")

    print("/** Precomputed note values for the wave audio channel. */")
    print("const ushort_t rom_notes_wave[NT_COUNT] = {")
    print(format_c_array(wave_entries))
    print("};\n")

    input()

if __name__ == "__main__":
    main()