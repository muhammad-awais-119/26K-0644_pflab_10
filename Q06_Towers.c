#include <stdio.h>

#define N 6

void grow(int heights[], int n) {
    if (n == 0) return;
    heights[n - 1] += (int)(heights[n - 1] * 0.10);
    grow(heights, n - 1);
}

int tallest(int heights[], int n) {
    if (n == 1) return 0;
    int best = tallest(heights, n - 1);
    return (heights[n - 1] > heights[best]) ? n - 1 : best;
}

int search(int heights[], int n, int target) {
    if (n == 0) return -1;
    if (heights[n - 1] == target) return n - 1;
    return search(heights, n - 1, target);
}

int main(void) {
    int ids[N] = {101, 102, 103, 104, 105, 106};
    int heights[N] = {45, 120, 78, 200, 95, 150};

    grow(heights, N);
    printf("New heights: ");
    for (int i = 0; i < N; i++) printf("%d ", heights[i]);
    printf("\n");

    int index = tallest(heights, N);
    printf("Tallest: tower %d (%d m)\n", ids[index], heights[index]);

    int target;
    printf("Height to search: ");
    if (scanf("%d", &target) == 1) {
        index = search(heights, N, target);
        if (index == -1) printf("No tower has height %d m\n", target);
        else printf("Tower %d is %d m\n", ids[index], heights[index]);
    }
    return 0;
}
