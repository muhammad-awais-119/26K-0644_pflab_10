#include <stdio.h>

#define RECORD_SIZE 23

int main(void) {
    char category[13];
    double amount;

    printf("Category: ");
    if (scanf("%12s", category) != 1) return 1;
    printf("Amount: ");
    if (scanf("%lf", &amount) != 1) return 1;

    FILE *fp = fopen("expenses.txt", "ab");
    if (fp == NULL) { perror("expenses.txt"); return 1; }
    fprintf(fp, "%-12s %9.2f\n", category, amount);
    fclose(fp);

    fp = fopen("expenses.txt", "rb+");
    if (fp == NULL) { perror("expenses.txt"); return 1; }

    char cat1[13], cat2[13];
    double amt1, amt2;
    if (fseek(fp, -2L * RECORD_SIZE, SEEK_END) == 0 &&
        fscanf(fp, "%12s %lf", cat1, &amt1) == 2 &&
        fscanf(fp, "%12s %lf", cat2, &amt2) == 2) {
        printf("Latest two: %s %.2f, %s %.2f\n", cat1, amt1, cat2, amt2);
    } else {
        printf("Could not read the latest two expenses.\n");
    }

    int entry;
    printf("Entry to fix: ");
    if (scanf("%d", &entry) == 1) {
        printf("Correct amount: ");
        if (scanf("%lf", &amount) == 1 && entry > 0) {
            long position = (long)(entry - 1) * RECORD_SIZE;
            if (fseek(fp, position, SEEK_SET) == 0 &&
                fscanf(fp, "%12s %lf", category, &amt1) == 2) {
                fseek(fp, position, SEEK_SET);
                fprintf(fp, "%-12s %9.2f\n", category, amount);
                fflush(fp);
            } else {
                printf("Invalid entry number.\n");
            }
        }
    }

    rewind(fp);
    double total = 0.0;
    while (fscanf(fp, "%12s %lf", category, &amount) == 2) {
        printf("%s %.2f\n", category, amount);
        total += amount;
    }
    printf("Total: %.2f\n", total);

    fclose(fp);
    return 0;
}
