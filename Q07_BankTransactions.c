#include <stdio.h>

#define N 7

int finalBalance(int trans[], int n, int balance) {
    if (n == 0) return balance;
    return finalBalance(trans, n - 1, balance + trans[n - 1]);
}

int totalDeposits(int trans[], int n) {
    if (n == 0) return 0;
    return (trans[n - 1] > 0 ? trans[n - 1] : 0)
           + totalDeposits(trans, n - 1);
}

int copyLarge(int trans[], int i, int n, int large[], int k) {
    if (i == n) return k;
    if (trans[i] <= -10000) {
        large[k] = trans[i];
        return copyLarge(trans, i + 1, n, large, k + 1);
    }
    return copyLarge(trans, i + 1, n, large, k);
}

int main(void) {
    int startingBalance = 20000;
    int trans[N] = {20000, -5000, -12000, 8000, -25000, -2500, 15000};
    int large[N];

    printf("Final balance: %d\n", finalBalance(trans, N, startingBalance));
    printf("Total deposits: %d\n", totalDeposits(trans, N));

    int count = copyLarge(trans, 0, N, large, 0);
    printf("Large withdrawals (%d): ", count);
    for (int i = 0; i < count; i++) printf("%d ", large[i]);
    printf("\n");

    return 0;
}
