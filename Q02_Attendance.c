#include <stdio.h>

#define RECORD_SIZE 24
#define TOTAL_STUDENTS 5
#define TOTAL_LECTURES 20

int main(void) {
    FILE *fp = fopen("attendance.txt", "w");
    if (fp == NULL) { perror("attendance.txt"); return 1; }

    fprintf(fp, "%-3d %-15s %3d\n", 1, "Ayesha", 18);
    fprintf(fp, "%-3d %-15s %3d\n", 2, "Bilal", 14);
    fprintf(fp, "%-3d %-15s %3d\n", 3, "Hamza", 20);
    fprintf(fp, "%-3d %-15s %3d\n", 4, "Sana", 12);
    fprintf(fp, "%-3d %-15s %3d\n", 5, "Zainab", 16);
    fclose(fp);

    fp = fopen("attendance.txt", "rb+");
    if (fp == NULL) { perror("attendance.txt"); return 1; }

    int roll, attended;
    char name[16];

    printf("Roll number: ");
    if (scanf("%d", &roll) == 1) {
        if (roll >= 1 && roll <= TOTAL_STUDENTS &&
            fseek(fp, (long)(roll - 1) * RECORD_SIZE, SEEK_SET) == 0 &&
            fscanf(fp, "%d %15s %d", &roll, name, &attended) == 3) {
            double percentage = attended * 100.0 / TOTAL_LECTURES;
            printf("%s: %d / %d (%.1f%%)%s\n", name, attended,
                   TOTAL_LECTURES, percentage,
                   percentage < 75.0 ? " Short attendance" : "");
        } else {
            printf("Invalid roll number or record.\n");
        }
    }

    int leave;
    printf("Roll number for leave: ");
    if (scanf("%d", &roll) == 1) {
        printf("Lectures: ");
        if (scanf("%d", &leave) == 1) {
            if (roll < 1 || roll > TOTAL_STUDENTS || leave < 0) {
                printf("Invalid input.\n");
            } else {
                long position = (long)(roll - 1) * RECORD_SIZE;
                if (fseek(fp, position, SEEK_SET) == 0 &&
                    fscanf(fp, "%d %15s %d", &roll, name, &attended) == 3) {
                    attended += leave;
                    if (attended > TOTAL_LECTURES) attended = TOTAL_LECTURES;
                    fseek(fp, position, SEEK_SET);
                    fprintf(fp, "%-3d %-15s %3d\n", roll, name, attended);
                    fflush(fp);
                    printf("%s: now %d / %d (%.1f%%)\n", name, attended,
                           TOTAL_LECTURES, attended * 100.0 / TOTAL_LECTURES);
                } else {
                    printf("Could not find that record.\n");
                }
            }
        }
    }

    int lastRoll, lastAttended;
    char lastName[16];
    if (fseek(fp, -RECORD_SIZE, SEEK_END) == 0 &&
        fscanf(fp, "%d %15s %d", &lastRoll, lastName, &lastAttended) == 3) {
        printf("Last record: %d %s %d\n", lastRoll, lastName, lastAttended);
    }

    fclose(fp);
    return 0;
}
