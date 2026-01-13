#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>


void clear() { printf("\033[2J\033[H"); }

int main() {
    srand(time(NULL));

    /* 1. FAKE CRASH */
    clear();
    printf("KERNEL PANIC\n");
    sleep(1);
    printf("fatal error at 0xDEADBEEF\n");
    sleep(1);
    printf("system halted.\n");
    sleep(2);

    /* 2. FAKE REBOOT */
    clear();
    printf("rebooting");
    fflush(stdout);
    for (int i = 0; i < 6; i++) {
        printf(".");
        fflush(stdout);
        usleep(300000);
    }
    sleep(1);

    /* 3. TEXT GRAVITY */
    clear();
    char msg[] = "GRAVITY";
    for (int y = 0; y < 20; y++) {
        clear();
        for (int i = 0; i < y; i++) printf("\n");
        printf("%s\n", msg);
        usleep(120000);
    }
    sleep(1);

    /* 4. FIREWORKS */
    /* 4. FIREWORKS — FIXED */
for (int t = 0; t < 30; t++) {
    clear();
    int cx = rand() % 60 + 10;
    int cy = rand() % 15 + 4;

    for (int r = 1; r < 8; r++) {
        clear();
        for (int a = 0; a < 360; a += 20) {
            int x = cx + r * cos(a * 3.14 / 180);
            int y = cy + r * sin(a * 3.14 / 180);
            if (x > 0 && x < 80 && y > 0 && y < 24)
                printf("\033[%d;%dH*", y, x);
        }
        fflush(stdout);
        usleep(60000);
    }
}


    /* 5. VHS GLITCH */
    for (int t = 0; t < 80; t++) {
        clear();
        for (int y = 0; y < 24; y++) {
            int shift = rand() % 6;
            for (int i = 0; i < shift; i++) putchar(' ');
            for (int x = 0; x < 80; x++)
                putchar(rand() % 2 ? '#' : ' ');
            putchar('\n');
        }
        usleep(50000);
    }

    clear();
    printf("done.\n");
}
