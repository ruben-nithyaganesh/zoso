#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "parser.h"
#include "text_renderer.h"



void core_loop() {
    while(1) {
        char input[INPUT_SIZE + 1];

        printf(":");
        scanf("%s", input);

        input[INPUT_SIZE] = 0;

        printf("'%s'\n", input);
        
        Action action = parse(input);
        
        switch(action.type) {
            case QUIT:
                printf("Quitting.\n"); 
                exit(0);
                break;
            case TOGGLE_LEFT_MODE:
                TOGGLE(LEFT_MODE);
                printf("Left handed mode %s.\n", (LEFT_MODE ? "enabled" : "disabled")); 
                break;
            case TOGGLE_HIGH_TO_LOW:
                TOGGLE(HIGH_TO_LOW);
                printf("High to low %s.\n", (HIGH_TO_LOW ? "enabled" : "disabled")); 
                break;
            case TOGGLE_NUMBER_MODE:
                TOGGLE(NUMBER_MODE);
                printf("Number mode %s.\n", (NUMBER_MODE ? "enabled" : "disabled")); 
                break;
            case DISPLAY_NOTE:
            {
                clear_fretboard();
                fret_marker = '*';
                Note note = action.note;
                Note_Set set = all_note_locations(note, standard_tuning);
                render_note_set(set);
                show_fretboard();
            }
            break;
            case DISPLAY_CHORD:
            {
                clear_fretboard();
                Note root = action.note;
                int note_number = 1;
                for(int i = 0; i < chord_lengths[action.chord_type]; i++) {
                    Note note = ((root + chords[action.chord_type][i]) % 12);
                    fret_marker = note_number + '0';
                    Note_Set set = all_note_locations(note, standard_tuning);
                    render_note_set(set);
                    note_number += 2;
                }
                show_fretboard();
            }
            break;
            case CHANGE_FRET_WINDOW:
            {
                fret_window_start = action.fret_start;
                fret_window_end = action.fret_end;
                printf("window changed to %d:%d", fret_window_start, fret_window_end);
            }
            break;
            case UNCRECOGNISED_ACTION:
                printf("Did not recognise the entered command.\n");
                break;
            default:
                break;
        }
        // if(MATCH(input, "showb")) {
        //     clear_fretboard();
        //     Note_Set set = all_note_locations(B, standard_tuning);
        //     render_note_set(set);
        //     show_fretboard();
        // }
        // else if(MATCH(input, "cmaj")) {
        //     clear_fretboard();
        //     Note_Set cs = all_note_locations(C, standard_tuning);
        //     render_note_set(cs);
        //     Note_Set es = all_note_locations(E, standard_tuning);
        //     render_note_set(es);
        //     Note_Set fs = all_note_locations(G, standard_tuning);
        //     render_note_set(fs);
        //     show_fretboard();
        // }
        // else if(MATCH(input, "amin")) {
        //     clear_fretboard();
        //     Note_Set cs = all_note_locations(A, standard_tuning);
        //     render_note_set(cs);
        //     Note_Set es = all_note_locations(C, standard_tuning);
        //     render_note_set(es);
        //     Note_Set fs = all_note_locations(E, standard_tuning);
        //     render_note_set(fs);
        //     show_fretboard();
        // }
        // else {
        //     clear_fretboard();
        //     switch(input[0]) {
        //         case 'C': case 'c':
        //             render_chord_shape(C, Major_C);
        //             show_fretboard();
        //         break;
        //         case 'A': case 'a':
        //             render_chord_shape(C, Major_A);
        //             show_fretboard();
        //         break;
        //         case 'G': case 'g':
        //             render_chord_shape(C, Major_G);
        //             show_fretboard();
        //         break;
        //         case 'E': case 'e':
        //             render_chord_shape(C, Major_E);
        //             show_fretboard();
        //         break;
        //         case 'D': case 'd':
        //             render_chord_shape(C, Major_D);
        //             show_fretboard();
        //         break;
        //         case 'q': case 'Q':
        //             printf("Quitting.\n");
        //             exit(0);
        //         break;
        //     }
        // }
    }
}

int main() 
{
    printf("Zoso\n");
    core_loop();
    return 0;   
}
