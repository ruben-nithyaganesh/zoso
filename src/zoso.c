#include <stdio.h>
#include <stdlib.h>
#include "core.h"
#include "text_renderer.h"


#define MATCH(input, str) matches(input, str, sizeof(str))

int matches(char s1[], char s2[], int size) {
    for(int i = 0; i < size; i++) {
        if(s1[i] != s2[i]) {
            return 0;
        }
    }
    return 1;
}

void core_loop() {
    while(1) {
        char input[10];
        printf(":");
        scanf("%s", input);
        input[9] = 0;
        printf("'%s'\n", input);
        if(MATCH(input, "lm")) {
            TOGGLE(LEFT_MODE);
        }
        else if(MATCH(input, "htl")) {
            TOGGLE(HIGH_TO_LOW);
        }
        else if(MATCH(input, "nm")) {
            TOGGLE(NUMBER_MODE);
        }
        else {
            clear_fretboard();
            switch(input[0]) {
                case 'C': case 'c':
                    render_chord_shape(C, Major_C);
                    show_fretboard();
                break;
                case 'A': case 'a':
                    render_chord_shape(C, Major_A);
                    show_fretboard();
                break;
                case 'G': case 'g':
                    render_chord_shape(C, Major_G);
                    show_fretboard();
                break;
                case 'E': case 'e':
                    render_chord_shape(C, Major_E);
                    show_fretboard();
                break;
                case 'D': case 'd':
                    render_chord_shape(C, Major_D);
                    show_fretboard();
                break;
                case 'q': case 'Q':
                    printf("Quitting.\n");
                    exit(0);
                break;
            }
        }
    }
}

int main() 
{
    printf("Zoso\n");
    core_loop();
    return 0;
}
