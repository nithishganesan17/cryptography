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

    // Calculate score for each possible plaintext
    float scores[num_plaintexts];
    for (int i = 0; i < num_plaintexts; i++) {
        int plaintext_frequency[ALPHABET_SIZE] = {0};
        calculate_frequency(plaintexts[i], plaintext_frequency);

        float score = 0.0;
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            score += abs((float)ciphertext_frequency[j] - english_frequency[j]) * (float)plaintext_frequency[j];
        }
        scores[i] = score;
    }

    // Sort plaintexts based on score
    for (int i = 0; i < num_plaintexts - 1; i++) {
        for (int j = 0; j < num_plaintexts - i - 1; j++) {
            if (scores[j] > scores[j + 1]) {
                float temp_score = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp_score;

                char *temp_plaintext = plaintexts[j];
                plaintexts[j] = plaintexts[j + 1];
                plaintexts[j + 1] = temp_plaintext;
            }
        }
    }
}

int main() {
    char ciphertext[] = "KhoorZruog"; // Example ciphertext
    int num_plaintexts = 10;          // Number of possible plaintexts to generate

    // Generate possible plaintexts by shifting each letter
    char *plaintexts[num_plaintexts];
    for (int i = 0; i < num_plaintexts; i++) {
        plaintexts[i] = strdup(ciphertext);
        for (int j = 0; plaintexts[i][j] != '\0'; j++) {
            if (isalpha(plaintexts[i][j])) {
                plaintexts[i][j] = 'a' + (plaintexts[i][j] - 'a' - i + ALPHABET_SIZE) % ALPHABET_SIZE;
            }
        }
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

