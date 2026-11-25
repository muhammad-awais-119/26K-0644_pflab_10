#include <stdio.h>
#include <string.h>

int countRepeat(char s[], int i) {
    if (s[i] == '\0') return 0;
    if (s[i + 1] == s[i]) return 1 + countRepeat(s, i + 1);
    return 1;
}

void compress(char s[], int i, char out[], int j) {
    if (s[i] == '\0') {
        out[j] = '\0';
        return;
    }

    int count = countRepeat(s, i);
    out[j] = s[i];
    out[j + 1] = (char)('0' + count);
    compress(s, i + count, out, j + 2);
}

void expand(char in[], int i, char out[], int j) {
    if (in[i] == '\0') {
        out[j] = '\0';
        return;
    }

    int count = in[i + 1] - '0';
    if (count < 1 || count > 9) {
        out[j] = '\0';
        return;
    }

    for (int k = 0; k < count; k++) out[j + k] = in[i];
    expand(in, i + 2, out, j + count);
}

int main(void) {
    char original[200];
    char compressed[400];
    char expanded[400];

    printf("Enter a string (no run longer than 9): ");
    if (scanf("%199s", original) != 1) return 1;

    compress(original, 0, compressed, 0);
    expand(compressed, 0, expanded, 0);

    printf("Original: %s\n", original);
    printf("Compressed: %s\n", compressed);
    printf("Expanded: %s\n", expanded);
    printf("Match: %s\n", strcmp(original, expanded) == 0 ? "Yes" : "No");

    return 0;
}
