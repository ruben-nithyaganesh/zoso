#ifndef CORE
#define CORE

#define NUM_NOTES 12
#define FRETBOARD_SIZE 24
#define STRINGS 6

#define DEBUG_MODE 1
#if DEBUG_MODE
    #define DEBUG(msg) printf(msg)
#else
    #define DEBUG(msg) do {} while (0)
#endif

typedef unsigned short u16;
typedef unsigned char u8;

typedef enum Chord_Shape {
    Major_C,
    Major_A,
    Major_G,
    Major_E,
    Major_D,

    n_chord_shapes
} Chord_Shape;

typedef enum Interval {
    UNISON,
    MINOR_SECOND,
    MAJOR_SECOND,
    MINOR_THIRD,
    MAJOR_THIRD,
    PERFECT_FOURTH,
    TRITONE,
    PERFECT_FIFTH,
    MINOR_SIXTH,
    MAJOR_SIXTH,
    MINOR_SEVENTH,
    MAJOR_SEVENTH,
    OCTAVE
} Interval;

typedef enum Note {
    C           = 0,
    C_SHARP     = 1,
    D_FLAT      = 1,
    D           = 2,
    D_SHARP     = 3,
    E_FLAT      = 3,
    E           = 4,
    F           = 5,
    F_SHARP     = 6,
    G_FLAT      = 6,
    G           = 7,
    G_SHARP     = 8,    
    A_FLAT      = 8,
    A           = 9,
    A_SHARP     = 10,
    B_FLAT      = 10,
    B           = 11
} Note;

typedef enum Scale_Type {
    MAJOR,
    MINOR
} Scale_Type;

typedef enum Chord_Type {
    Chord_MAJOR,
    Chord_SEVENTH,
    Chord_MAJOR_7,
    Chord_MINOR,
    Chord_MINOR_7,

    n_chords
} Chord_Type;

const int chords[][n_chords] = {
    [Chord_MAJOR]       = {0, MAJOR_THIRD, PERFECT_FIFTH},
    [Chord_SEVENTH]     = {0, MAJOR_THIRD, PERFECT_FIFTH, MINOR_SEVENTH},
    [Chord_MAJOR_7]     = {0, MAJOR_THIRD, PERFECT_FIFTH, MAJOR_SEVENTH},
    [Chord_MINOR]       = {0, MINOR_THIRD, PERFECT_FIFTH},
    [Chord_MINOR_7]     = {0, MINOR_THIRD, PERFECT_FIFTH, MINOR_SEVENTH}
};

const int chord_lengths[n_chords] = {
    [Chord_MAJOR]    = 3,
    [Chord_SEVENTH]  = 4,
    [Chord_MAJOR_7]  = 4,
    [Chord_MINOR]    = 3,
    [Chord_MINOR_7]  = 4
};

#define TOGGLEABLE(name, default) int name = default; \
void toggle_##name() { \
    if(name) { \
        name = 0; \
    } \
    else { \
        name = 1; \
    } \
}

TOGGLEABLE(LEFT_MODE, 0)
TOGGLEABLE(HIGH_TO_LOW, 0)
TOGGLEABLE(NUMBER_MODE, 0)

#define TOGGLE(name) toggle_##name()

static char fret_marker = '*';

typedef enum Action_Type {
    TOGGLE_LEFT_MODE,
    TOGGLE_HIGH_TO_LOW,
    TOGGLE_NUMBER_MODE,
    DISPLAY_NOTE,
    DISPLAY_CHORD,
    DISPLAY_SCALE,
    CHANGE_FRET_WINDOW,
    QUIT,

    UNCRECOGNISED_ACTION
} Action_Type;

typedef struct Action {
    Action_Type type;
    Note note;
    Scale_Type scale_type;
    Chord_Type chord_type;
    Chord_Shape chord_shape;
    int fret_start, fret_end;
} Action;

typedef struct Note_Set {
    u8 notes[FRETBOARD_SIZE * STRINGS];
    u8 size;
} Note_Set;

int major_scale[] = {0, 2, 4, 5, 7, 9, 11};
int minor_scale[] = {0, 2, 3, 5, 7, 8, 10};


int TOTAL_FRETBOARD_LOCATIONS = FRETBOARD_SIZE * STRINGS;

#define SHARPS 0
#define FLATS 1
const char *note_strings[2][NUM_NOTES] = {
    { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"},
    { "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"}
};

int fret_window_start = 0;
int fret_window_end = FRETBOARD_SIZE - 1;

Note standard_tuning[STRINGS] = { E, B, G, D, A, E };

Note get_relative_note(Note start, int offset) {
    int new_note_n = start + offset;
    Note new_note = new_note_n % 12;
    return new_note;
}

Note_Set all_note_locations(Note note, Note tuning[STRINGS]) {
    Note_Set set;
    set.size = TOTAL_FRETBOARD_LOCATIONS;
    for(int i=0; i<TOTAL_FRETBOARD_LOCATIONS; i++) { set.notes[i] = 0; }

    int target_note = (int) note;
    for(int string_i = 0; string_i < STRINGS; string_i++) {
        int fret = 0;
        if(tuning[string_i] == target_note) {
            fret = NUM_NOTES - 1;
        }
        else {
            int current_note = (int) tuning[string_i] + 1;
            if (current_note == 12) { current_note = 0; }
            int diff = current_note - target_note;
            if(diff == 0) { fret = 0; }
            else if(diff < 0) { fret = -(diff); }
            else { fret = NUM_NOTES - diff; }
        }
        while(fret < FRETBOARD_SIZE) {
            set.notes[string_i * FRETBOARD_SIZE + fret] = fret_marker;
            //printf("%s found at string %s, fret %d\n", note_strings[0][note], note_strings[0][tuning[string_i]], fret+1);
            fret += NUM_NOTES;
        }
    }
    return set;
}



#endif