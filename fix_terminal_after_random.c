#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int w = 80, h = 24;

    // chaos
    for (int t = 0; t < 200; t++) {
        printf("\033[H");
        for (int i = 0; i < w*h; i++)
            putchar(rand() % 94 + 33);
        usleep(8000);
    }

    // snap back
    printf("\033[2J\033[H");
    printf("…okay.\n");
}
