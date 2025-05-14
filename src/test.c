#include <stdio.h>

int main() {
    char word[3] = "a";
    printf("len %d\n", (int) (sizeof(word) / sizeof(word[0])));
}