#include <stdio.h>
#include <string.h>

#define ROOM_COUNT 10
#define FIRST_ROOM 101
#define RECORD_SIZE 39
#define RATE 8000.0

int main(void) {
    FILE *fp = fopen("hotel.txt", "w");
    if (fp == NULL) { perror("hotel.txt"); return 1; }

    for (int i = 0; i < ROOM_COUNT; i++)
        fprintf(fp, "%3d %c %-20s %2d %8.2f\n",
                FIRST_ROOM + i, 'F', "-", 0, RATE);
    fclose(fp);

    fp = fopen("hotel.txt", "rb+");
    if (fp == NULL) { perror("hotel.txt"); return 1; }

    int room, nights, storedRoom, storedNights;
    char status, guest[21];
    char guests[ROOM_COUNT][21];
    int rooms[ROOM_COUNT];

    printf("Check-in room: ");
    if (scanf("%d", &room) == 1) {
        printf("Name: ");
        if (scanf("%20s", guest) == 1) {
            printf("Nights: ");
            if (scanf("%d", &nights) == 1) {
                if (room < FIRST_ROOM || room >= FIRST_ROOM + ROOM_COUNT || nights <= 0) {
                    printf("Invalid room or number of nights.\n");
                } else {
                    long position = (long)(room - FIRST_ROOM) * RECORD_SIZE;
                    fseek(fp, position, SEEK_SET);
                    if (fscanf(fp, "%d %c %20s %d %lf",
                               &storedRoom, &status, guests[0], &storedNights, &(double){0}) == 5) {
                        if (status == 'F') {
                            fseek(fp, position, SEEK_SET);
                            fprintf(fp, "%3d %c %-20s %2d %8.2f\n",
                                    room, 'B', guest, nights, RATE);
                            fflush(fp);
                            printf("Room %d booked\n", room);
                        } else {
                            printf("Room already booked.\n");
                        }
                    }
                }
            }
        }
    }

    rewind(fp);
    for (int i = 0; i < ROOM_COUNT; i++) {
        double rate;
        if (fscanf(fp, "%d %c %20s %d %lf", &rooms[i], &status,
                   guests[i], &storedNights, &rate) != 5) {
            rooms[i] = FIRST_ROOM + i;
            strcpy(guests[i], "-");
        }
    }

    printf("Search name: ");
    if (scanf("%20s", guest) == 1) {
        int found = 0;
        for (int i = 0; i < ROOM_COUNT; i++) {
            if (strcmp(guests[i], guest) == 0) {
                printf("%s is in room %d\n", guest, rooms[i]);
                found = 1;
                break;
            }
        }
        if (!found) printf("Guest not found.\n");
    }

    printf("Check-out room: ");
    if (scanf("%d", &room) == 1) {
        if (room < FIRST_ROOM || room >= FIRST_ROOM + ROOM_COUNT) {
            printf("Invalid room number.\n");
        } else {
            long position = (long)(room - FIRST_ROOM) * RECORD_SIZE;
            double rate;
            fseek(fp, position, SEEK_SET);
            if (fscanf(fp, "%d %c %20s %d %lf",
                       &storedRoom, &status, guest, &storedNights, &rate) == 5) {
                if (status == 'B') {
                    printf("Bill: %d x %.2f = %.2f\n",
                           storedNights, rate, storedNights * rate);
                    fseek(fp, position, SEEK_SET);
                    fprintf(fp, "%3d %c %-20s %2d %8.2f\n",
                            storedRoom, 'F', "-", 0, RATE);
                    fflush(fp);
                } else {
                    printf("Room is already free.\n");
                }
            }
        }
    }

    fclose(fp);
    return 0;
}
