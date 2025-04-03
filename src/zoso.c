#include <stdio.h>
#include "core.h"
#include "text_renderer.h"

int main() 
{
    printf("Zoso\n");
    left_mode(1);
    number_mode(0);
    high_to_low(0);
    render_chord_shape(C, Major_C);
    show_fretboard();
    clear_fretboard();
    render_chord_shape(C, Major_A);
    show_fretboard();
    clear_fretboard();
    render_chord_shape(C, Major_G);
    show_fretboard();
    clear_fretboard();
    render_chord_shape(C, Major_E);
    show_fretboard();
    clear_fretboard();
    render_chord_shape(C, Major_D);
    show_fretboard();
    return 0;
}