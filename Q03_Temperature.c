#include <stdio.h>

#define RECORD_SIZE 17
#define CITY_COUNT 5

int main(void) {
    FILE *fp = fopen("temperature.txt", "w");
    if (fp == NULL) { perror("temperature.txt"); return 1; }

    char city[CITY_COUNT][11];
    double temperature[CITY_COUNT];

    for (int i = 0; i < CITY_COUNT; i++) {
        printf("City %d name (max 10 characters): ", i + 1);
        if (scanf("%10s", city[i]) != 1) { fclose(fp); return 1; }
        printf("Temperature: ");
        if (scanf("%lf", &temperature[i]) != 1) { fclose(fp); return 1; }
        fprintf(fp, "%-10s %5.1f\n", city[i], temperature[i]);
    }
    fclose(fp);

    fp = fopen("temperature.txt", "rb+");
    if (fp == NULL) { perror("temperature.txt"); return 1; }

    int number;
    char readCity[11];
    double readTemp;

    printf("City number to view: ");
    if (scanf("%d", &number) == 1) {
        if (number >= 1 && number <= CITY_COUNT &&
            fseek(fp, (long)(number - 1) * RECORD_SIZE, SEEK_SET) == 0 &&
            fscanf(fp, "%10s %lf", readCity, &readTemp) == 2) {
            printf("%s %.1f\n", readCity, readTemp);
        } else {
            printf("Invalid city number or record.\n");
        }
    }

    printf("City number to correct: ");
    if (scanf("%d", &number) == 1) {
        printf("New temperature: ");
        if (scanf("%lf", &readTemp) == 1) {
            if (number >= 1 && number <= CITY_COUNT) {
                long position = (long)(number - 1) * RECORD_SIZE;
                if (fseek(fp, position, SEEK_SET) == 0 &&
                    fscanf(fp, "%10s %lf", readCity, &temperature[0]) == 2) {
                    fseek(fp, position, SEEK_SET);
                    fprintf(fp, "%-10s %5.1f\n", readCity, readTemp);
                    fflush(fp);
                    printf("%s updated to %.1f\n", readCity, readTemp);
                } else {
                    printf("Could not read that record.\n");
                }
            } else {
                printf("Invalid city number.\n");
            }
        }
    }

    rewind(fp);
    char hottestCity[11] = "";
    double hottest = -1.0e30;
    while (fscanf(fp, "%10s %lf", readCity, &readTemp) == 2) {
        if (readTemp > hottest) {
            hottest = readTemp;
            snprintf(hottestCity, sizeof hottestCity, "%s", readCity);
        }
    }
    if (hottestCity[0] != '\0')
        printf("Hottest city: %s (%.1f)\n", hottestCity, hottest);

    fclose(fp);
    return 0;
}
