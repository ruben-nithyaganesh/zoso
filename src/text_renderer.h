#ifndef TEXT_RENDERER
#define TEXT_RENDERER

#include <stdio.h>
#include "core.h"

char blank_fretboard[] = "||---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---||\n"
"||---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---||\n"
"||---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---||\n"
"||---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---||\n"
"||---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---||\n"
"||---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---||\n";


char fretboard[] = "||---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---||\n"
"||---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---||\n"
"||---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---||\n"
"||---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---||\n"
"||---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---||\n"
"||---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---||\n";

static const int FRETBOARD_STRING_WIDTH = sizeof("||---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---||\n") / sizeof(char);

char int_to_char[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o'};

int LEFT_MODE = 1;
void left_mode(int i) {   
    LEFT_MODE = i;
}

int HIGH_TO_LOW = 1;
void high_to_low(int i) {   
    HIGH_TO_LOW = i;
}

int NUMBER_MODE = 1;
void number_mode(int i) {
    NUMBER_MODE = i;
}

void mark_fretboard(int string, int fret)
{
    int render_fret = fret;
    if(LEFT_MODE) {
        render_fret = 23 - fret;
    }
    if(!HIGH_TO_LOW) {
        string = 5 - string;
    }

    char c = (NUMBER_MODE) ? int_to_char[fret] : '#';
    fretboard[3 + (FRETBOARD_STRING_WIDTH - 1) * string + 4 * render_fret] = c;
}

void clear_fretboard() {
    for (int i = 0; i < sizeof(fretboard) / sizeof(char); i++) {
        fretboard[i] = blank_fretboard[i];
    }
}

void show_fretboard() {
    printf("%s", fretboard);
    printf("\n");
}

void render_chord_shape(Note root, Chord_Shape shape) {
    switch (shape)
    {
        case Major_C:
            mark_fretboard(1, 0);
            mark_fretboard(3, 1);
            mark_fretboard(4, 2);
        break;
        case Major_A:
            mark_fretboard(1, 1);
            mark_fretboard(2, 1);
            mark_fretboard(3, 1);
        break;
        case Major_G:
            mark_fretboard(4, 1);
            mark_fretboard(5, 2);
            mark_fretboard(0, 2);
        break;
        case Major_E:
            mark_fretboard(4, 1);
            mark_fretboard(3, 1);
            mark_fretboard(2, 0);
        break;
        case Major_D:
            mark_fretboard(2, 1);
            mark_fretboard(0, 2);
            mark_fretboard(1, 3);
        break;
        default:
        break;
    }
}

#endif