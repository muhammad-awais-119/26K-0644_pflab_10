#include <stdio.h>

#define RECORD_SIZE 42

int main(void) {
    FILE *fp = fopen("items.txt", "w");
    if (fp == NULL) { perror("items.txt"); return 1; }

    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 1, "Rice",       250.00, 40);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 2, "Sugar",      160.00, 25);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 3, "Milk",       220.00, 30);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 4, "CookingOil", 560.00, 12);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 5, "Tea",        450.00, 18);
    fclose(fp);

    fp = fopen("items.txt", "rb+");
    if (fp == NULL) { perror("items.txt"); return 1; }

    double total = 0.0;
    int itemNo, quantity;

    while (1) {
        printf("\nItem no (0 to finish): ");
        if (scanf("%d", &itemNo) != 1) break;
        if (itemNo == 0) break;

        printf("Quantity: ");
        if (scanf("%d", &quantity) != 1) break;

        if (itemNo < 1 || itemNo > 5 || quantity <= 0) {
            printf("Invalid item number or quantity.\n");
            continue;
        }

        long position = (long)(itemNo - 1) * RECORD_SIZE;
        int storedNo, stock;
        char name[21];
        double price;

        if (fseek(fp, position, SEEK_SET) != 0 ||
            fscanf(fp, "%d %20s %lf %d", &storedNo, name, &price, &stock) != 4) {
            printf("Could not read item.\n");
            continue;
        }

        if (stock >= quantity) {
            double cost = quantity * price;
            printf("%s %d x %.2f = %.2f\n", name, quantity, price, cost);
            total += cost;
            stock -= quantity;

            if (fseek(fp, position, SEEK_SET) != 0) {
                printf("Could not update stock.\n");
                continue;
            }
            fprintf(fp, "%-4d %-20s %9.2f %5d\n", storedNo, name, price, stock);
            fflush(fp);
        } else {
            printf("Only %d %s in stock\n", stock, name);
        }
    }

    printf("\nTotal bill: %.2f\n", total);
    fclose(fp);
    return 0;
}
