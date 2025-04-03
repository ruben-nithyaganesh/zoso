#ifndef CORE
#define CORE

typedef enum Chord_Shape {
    Major_C,
    Major_A,
    Major_G,
    Major_E,
    Major_D
} Chord_Shape;

typedef enum Note {
    C = 0,
    C_SHARP = 1,
    D_FLAT = 1,
    D = 2,
    D_SHARP = 3,
    E_FLAT = 3,
    E = 4,
    F = 5,
    F_SHARP = 6,
    G_FLAT = 6,
    G = 7,
    G_SHARP = 8,
    A_FLAT = 8,
    A = 9,
    A_SHARP = 10,
    B_FLAT = 10,
    B = 11
} Note;

int major_scale[] = {0, 2, 4, 5, 7, 9, 11};

#define SHARPS 0
#define FLATS 1
const char *note_strings[2][12] = {
    { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"},
    { "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"}
};

Note standard_tuning[6] = { E, B, G, D, A, E };

#endif