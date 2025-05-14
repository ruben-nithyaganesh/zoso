#ifndef PARSER
#define PARSER

#include <stdlib.h>
#include "core.h"
#define INPUT_SIZE 20

#define MATCH(input, str) matches(input, str, sizeof(str) - 1)

int matches(char s1[], char s2[], int size) {
    for(int i = 0; i < size; i++) {
        if(s1[i] != s2[i]) {
            return 0;
        }
    }
    return 1;
}

#define NOTE_PAIR(n) {#n"_", ##n##_FLAT}, \
    {#n"^", ##n##_SHARP}, \
    {#n, ##n}

static struct {
    char str[3];
    Note n;
} string_note_pairs[] = {
    //NOTE_PAIR(A),
    {"a_", A_FLAT},
    {"a#", A_SHARP},
    {"a", A},
    {"b_", B_FLAT},
    {"b", B},
    {"c#", C_SHARP},
    {"c", C},
    {"d_", D_FLAT},
    {"d#", D_SHARP},
    {"d", D},
    {"e_", E_FLAT},
    {"e", E},
    {"f#", F_SHARP},
    {"f", F},
    {"g_", G_FLAT},
    {"g#", G_SHARP},
    {"g", G},
};

static int STRING_NOTE_PAIR_COUNT = sizeof(string_note_pairs) / sizeof(string_note_pairs[0]);

Note resolve_note(char* input_note) {
    for(int i = 0; i < STRING_NOTE_PAIR_COUNT; i++) {
        if(MATCH(input_note, string_note_pairs[i].str)) {
            return string_note_pairs[i].n;
        }
    }
    return -1;
}

Action parse(char input[INPUT_SIZE]) {
    Action action;
    action.type = UNCRECOGNISED_ACTION;

    if(MATCH(input, "q")) {
        action.type = QUIT;
    }
    else if(MATCH(input, "lm")) {
        action.type = TOGGLE_LEFT_MODE;
    }
    else if(MATCH(input, "htl")) {
        action.type = TOGGLE_HIGH_TO_LOW;
    }
    else if(MATCH(input, "nm")) {
        action.type = TOGGLE_NUMBER_MODE;
    }
    else if(MATCH(input, "f")) {
        action.type = CHANGE_FRET_WINDOW;
        if(MATCH(input, "freset")) {
            action.fret_start = 0;
            action.fret_end = FRETBOARD_SIZE - 1;   
        }
        else {
            action.fret_start = (int)(input[1]) - 48;
            action.fret_end = (int)(input[2]) - 48;
        }
    }
    else if(MATCH(input, "sn")) {
        action.type = DISPLAY_NOTE;
        char* input_note = input + (sizeof("sn") / sizeof(char) - 1);
        for(int i = 0; i < STRING_NOTE_PAIR_COUNT; i++) {
            if(MATCH(input_note, string_note_pairs[i].str)) {
                action.note = string_note_pairs[i].n;
                break;
            }
        }
    }
    else if(MATCH(input, "s7")) {
        action.type = DISPLAY_CHORD;
        action.chord_type = Chord_SEVENTH;
        char* input_note = input + (sizeof("s7") / sizeof(char) - 1);
        action.note = resolve_note(input_note);
        action.type = (action.note == -1) ? UNCRECOGNISED_ACTION : action.type;
    }
    else if(MATCH(input, "smaj7")) {
        action.type = DISPLAY_CHORD;
        action.chord_type = Chord_MAJOR_7;
        char* input_note = input + (sizeof("smaj7") / sizeof(char) - 1);
        action.note = resolve_note(input_note);
        action.type = (action.note == -1) ? UNCRECOGNISED_ACTION : action.type;
    }
    else if(MATCH(input, "smin7")) {
        action.type = DISPLAY_CHORD;
        action.chord_type = Chord_MINOR_7;
        char* input_note = input + (sizeof("smin7") / sizeof(char) - 1);
        action.note = resolve_note(input_note);
        action.type = (action.note == -1) ? UNCRECOGNISED_ACTION : action.type;
    }
    else if(MATCH(input, "smaj")) {
        action.type = DISPLAY_CHORD;
        action.chord_type = Chord_MAJOR;
        char* input_note = input + (sizeof("smaj") / sizeof(char) - 1);
        action.note = resolve_note(input_note);
        action.type = (action.note == -1) ? UNCRECOGNISED_ACTION : action.type;
    }
    else if(MATCH(input, "smin")) {
        action.type = DISPLAY_CHORD;
        action.chord_type = Chord_MINOR;
        char* input_note = input + (sizeof("smin") / sizeof(char) - 1);
        action.note = resolve_note(input_note);
        action.type = (action.note == -1) ? UNCRECOGNISED_ACTION : action.type;
    }

    return action;
}

#endif