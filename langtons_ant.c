#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define W 80
#define H 40

int g[H][W];

int main() {
    int x = W/2, y = H/2;
    int dir = 0; // 0 up, 1 right, 2 down, 3 left

    while (1) {
        system("clear");

        // turn + flip
        if (g[y][x]) dir = (dir + 3) % 4;
        else         dir = (dir + 1) % 4;
        g[y][x] ^= 1;

        // move
        if (dir == 0) y = (y - 1 + H) % H;
        if (dir == 1) x = (x + 1) % W;
        if (dir == 2) y = (y + 1) % H;
        if (dir == 3) x = (x - 1 + W) % W;

        // draw
        for (int j=0;j<H;j++) {
            for (int i=0;i<W;i++)
                printf(g[j][i] ? "██" : "  ");
            printf("\n");
        }

        usleep(60000);
    }
}
