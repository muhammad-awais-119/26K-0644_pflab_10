#include <stdio.h>

#define SIZE 5

int markZone(char map[][SIZE], int r, int c, char label) {
    if (r < 0 || r >= SIZE || c < 0 || c >= SIZE || map[r][c] != '*')
        return 0;

    map[r][c] = label;
    return 1
        + markZone(map, r - 1, c, label)
        + markZone(map, r + 1, c, label)
        + markZone(map, r, c - 1, label)
        + markZone(map, r, c + 1, label);
}

int main(void) {
    float temp[SIZE][SIZE] = {
        { 2.1f, -1.5f, -2.0f,  3.0f,  4.2f},
        { 1.8f, -0.5f,  2.5f,  3.1f, -1.0f},
        { 3.3f,  2.0f,  1.5f, -0.8f, -2.0f},
        {-1.2f,  3.4f,  4.0f,  3.8f, -0.6f},
        {-2.5f, -3.1f,  5.1f,  6.0f,  4.7f}
    };
    char map[SIZE][SIZE];

    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            map[r][c] = (temp[r][c] < 0.0f) ? '*' : '.';

    int zones = 0;
    char label = 'A';
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (map[r][c] == '*') {
                int size = markZone(map, r, c, label);
                printf("Zone %c: %d stations\n", label, size);
                zones++;
                label++;
            }
        }
    }

    printf("\nTotal zones: %d\n", zones);
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) printf("%c ", map[r][c]);
        printf("\n");
    }
    return 0;
}
