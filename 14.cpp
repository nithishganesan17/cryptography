#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void countFrequency(const char *ciphertext, int frequency[ALPHABET_SIZE]) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; ++i) {
        if (isalpha(ciphertext[i])) {
            int index = tolower(ciphertext[i]) - 'a';
            frequency[index]++;
        }
    }
}

void frequencyAttack(const char *ciphertext, int top_n) {
    int frequency[ALPHABET_SIZE] = {0};
    countFrequency(ciphertext, frequency);

    int sorted_frequency[ALPHABET_SIZE];
    memcpy(sorted_frequency, frequency, sizeof(int) * ALPHABET_SIZE);

    qsort(sorted_frequency, ALPHABET_SIZE, sizeof(int), compareIntegers);

    char english_frequency[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

    char substitution[ALPHABET_SIZE + 1];
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        substitution[sorted_frequency[i]] = english_frequency[i];
    }
    substitution[ALPHABET_SIZE] = '\0';

    // Print the top_n possible plaintexts based on frequency analysis
    printf("Possible plaintexts:\n");
    for (int i = 0; i < top_n; ++i) {
        printf("%d. ", i + 1);
        for (int j = 0; ciphertext[j] != '\0'; ++j) {
            if (isalpha(ciphertext[j])) {
                char plain_char = islower(ciphertext[j]) ? tolower(substitution[ciphertext[j] - 'a']) : toupper(substitution[ciphertext[j] - 'A']);
                printf("%c", plain_char);
            } else {
                printf("%c", ciphertext[j]);
            }
        }
        printf("\n");
    }
}

// Helper function for qsort
int compareIntegers(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    char ciphertext[] = "DRO VKRUW KLV RUJDQLVP LV DQ HUURU";
    int top_n = 10; // Specify the number of top possible plaintexts to display

    printf("Ciphertext: %s\n", ciphertext);
    frequencyAttack(ciphertext, top_n);

    return 0;
}
