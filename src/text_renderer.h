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

void mark_fretboard(int string, int fret, char c)
{
    int render_fret = fret;
    if(LEFT_MODE) {
        render_fret = 23 - fret;
    }
    if(!HIGH_TO_LOW) {
        string = 5 - string;
    }

    fretboard[3 + (FRETBOARD_STRING_WIDTH - 1) * string + 4 * render_fret] = c;
}

void clear_fretboard() {
    for (int i = 0; i < sizeof(fretboard) / sizeof(char); i++) {
        fretboard[i] = blank_fretboard[i];
    }
}

char* slice_fretboard(int start, int end) {
    if(LEFT_MODE) {
        start = FRETBOARD_SIZE - end;
        end = FRETBOARD_SIZE - start;
    }
    char sliced[sizeof(fretboard) / sizeof(fretboard[0])];
    int slice_index = 0;
    int fret_char_width = 4;
    for(int string = 0; string < STRINGS; string++) {
        //sliced[slice_index++] = '|';
        for(int i = 0; i < (end - start); i++) {
            for(int f = 0; f < fret_char_width; f++) {
                sliced[slice_index] = fretboard[(FRETBOARD_STRING_WIDTH-1)*string + start*fret_char_width + 1 + i*fret_char_width + f];
                slice_index += 1;
            }
        }
        sliced[slice_index++] = '|';
        sliced[slice_index++] = '\n';
    }
    printf("%s", sliced);
}

void show_fretboard() {
    printf("  ");
    int start = 4;
    int end = 8;
    for(int i = start+1; i < end; i++) {
        int ind = (LEFT_MODE == 1) ? i-1 : FRETBOARD_SIZE - i;
        if(ind == 3 || ind == 5 || ind == 7 || ind == 9 || ind == 15 || ind == 17 || ind == 19 || ind == 21) {
            printf(" .  ");
        }
        else if(ind == 12) {
            printf(". . ");
        }
        else {
            printf("    ");
        }
    }
    printf(" \n");
    printf("%s", slice_fretboard(start, end));
    printf("\n");
}

void render_chord_shape(Note root, Chord_Shape shape) {
    switch (shape)
    {
        case Major_C:
            mark_fretboard(1, 0, '*');
            mark_fretboard(3, 1, '*');
            mark_fretboard(4, 2, '*');
        break;
        case Major_A:
            mark_fretboard(1, 1, '*');
            mark_fretboard(2, 1, '*');
            mark_fretboard(3, 1, '*');
        break;
        case Major_G:
            mark_fretboard(4, 1, '*');
            mark_fretboard(5, 2, '*');
            mark_fretboard(0, 2, '*');
        break;
        case Major_E:
            mark_fretboard(4, 1, '*');
            mark_fretboard(3, 1, '*');
            mark_fretboard(2, 0, '*');
        break;
        case Major_D:
            mark_fretboard(2, 1, '*');
            mark_fretboard(0, 1, '*');
            mark_fretboard(1, 2, '*');
        break;
        default:
        break;
    }
}

void render_note_set(Note_Set set) {
    for(int string = 0; string < STRINGS; string++) {
        for(int fret = 0; fret < FRETBOARD_SIZE; fret++) {
            if(set.notes[string * FRETBOARD_SIZE + fret]) {
                char c = (NUMBER_MODE) ? int_to_char[fret] : set.notes[string * FRETBOARD_SIZE + fret];
                mark_fretboard(string, fret, c);
            }
        } 
    }
}

#endif