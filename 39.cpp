#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to calculate the frequency of letters in the given text
void calculate_frequency(const char *text, int *frequency) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            int index = tolower(text[i]) - 'a';
            frequency[index]++;
        }
    }
}

// Function to perform a letter frequency attack and produce possible plaintexts
void letter_frequency_attack(const char *ciphertext, char *plaintexts[], int num_plaintexts) {
    int ciphertext_frequency[ALPHABET_SIZE] = {0};
    calculate_frequency(ciphertext, ciphertext_frequency);

    // English language letter frequency (approximate)
    float english_frequency[ALPHABET_SIZE] = {
        8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 0.772, 4.025,
        2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074
    };

    // Iterate through possible additive keys
    for (int key = 0; key < ALPHABET_SIZE; key++) {
        char *potential_plaintext = strdup(ciphertext);

        // Decrypt using the current key
        for (int i = 0; potential_plaintext[i] != '\0'; i++) {
            if (isalpha(potential_plaintext[i])) {
                char base = isupper(potential_plaintext[i]) ? 'A' : 'a';
                potential_plaintext[i] = ((potential_plaintext[i] - base - key + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
            }
        }

        // Calculate score for this potential plaintext
        int plaintext_frequency[ALPHABET_SIZE] = {0};
        calculate_frequency(potential_plaintext, plaintext_frequency);

        float score = 0.0;
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            score += abs((float)ciphertext_frequency[j] - english_frequency[j]) * (float)plaintext_frequency[j];
        }

        // Insert the potential plaintext into the list of plaintexts in sorted order
        int i;
        for (i = num_plaintexts - 1; i >= 0 && score < plaintexts[i][0]; i--) {
            strcpy(plaintexts[i + 1], plaintexts[i]);
        }
        strcpy(plaintexts[i + 1], potential_plaintext);

        free(potential_plaintext);
    }
}

int main() {
    char ciphertext[] = "RovvyNygbi"; // Example ciphertext
    int num_plaintexts = 10;          // Number of possible plaintexts to generate

    // Allocate memory for potential plaintexts
    char *plaintexts[num_plaintexts];
    for (int i = 0; i < num_plaintexts; i++) {
        plaintexts[i] = malloc(strlen(ciphertext) + 1);
    }

    // Perform letter frequency attack
    letter_frequency_attack(ciphertext, plaintexts, num_plaintexts);

    // Print top 10 possible plaintexts
    printf("Top 10 Possible Plaintexts:\n");
    for (int i = 0; i < num_plaintexts && i < 10; i++) {
        printf("%s\n", plaintexts[i]);
        free(plaintexts[i]);
    }

    return 0;
}

