#include <stdio.h>

#define N 10

void buildScores(int change[], int score[], int i, int n, int current) {
    if (i == n) return;
    current += change[i];
    score[i] = current;
    buildScores(change, score, i + 1, n, current);
}

int countLow(int score[], int n) {
    if (n == 0) return 0;
    return (score[n - 1] < 50) + countLow(score, n - 1);
}

void reverse(int arr[], int left, int right) {
    if (left >= right) return;
    int temp = arr[left];
    arr[left] = arr[right];
    arr[right] = temp;
    reverse(arr, left + 1, right - 1);
}

int main(void) {
    int start = 70;
    int change[N] = {5, -8, -10, -12, 4, 6, 3, 7, -2, 5};
    int score[N];

    buildScores(change, score, 0, N, start);

    printf("Daily scores: ");
    for (int i = 0; i < N; i++) printf("%d ", score[i]);
    printf("\nDays below 50: %d\n", countLow(score, N));

    reverse(score, 0, N - 1);
    printf("Latest first: ");
    for (int i = 0; i < N; i++) printf("%d ", score[i]);
    printf("\n");

    return 0;
}
