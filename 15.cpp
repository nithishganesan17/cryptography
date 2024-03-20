#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_PLAINTEXT_LENGTH 1000

float eng_letter_freq[ALPHABET_SIZE] = {
    0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, // A-G
    0.0609, 0.0697, 0.0015, 0.0077, 0.0403, 0.0241, 0.0675, // H-N
    0.0751, 0.0193, 0.0009, 0.0599, 0.0633, 0.0906, 0.0276, // O-U
    0.0098, 0.0236, 0.0015, 0.0197, 0.0007                  // V-Z
};

float calculate_likelihood(char *text, int length) {
    float likelihood = 1.0;
    int count[ALPHABET_SIZE] = {0};
    int total_letters = 0;
    for (int i = 0; i < length; i++) {
        char c = tolower(text[i]);
        if (isalpha(c)) {
            count[c - 'a']++;
            total_letters++;
        }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        float observed_freq = (float)count[i] / total_letters;
        likelihood *= eng_letter_freq[i] * observed_freq;
    }
    return likelihood;
}

// Function to decrypt the ciphertext using a given key
void decrypt(char *ciphertext, int *key, int key_length, int ciphertext_length) {
    char plaintext[MAX_PLAINTEXT_LENGTH];
    for (int i = 0; i < ciphertext_length; i++) {
        char c = ciphertext[i];
        if (isalpha(c)) {
            char decrypted_char = ((c - 'a') - key[i % key_length] + ALPHABET_SIZE) % ALPHABET_SIZE + 'a';
            plaintext[i] = decrypted_char;
        } else {
            plaintext[i] = c;
        }
    }
    plaintext[ciphertext_length] = '\0';
    printf("Decrypted plaintext: %s\n", plaintext);
}

int main() {
    char ciphertext[MAX_PLAINTEXT_LENGTH];
    int key[MAX_PLAINTEXT_LENGTH];
    int key_length, ciphertext_length;

    // Input the ciphertext
    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_PLAINTEXT_LENGTH, stdin);
    ciphertext_length = strlen(ciphertext) - 1; // Remove newline character

    // Input the key
    printf("Enter the key length: ");
    scanf("%d", &key_length);
    printf("Enter the key: ");
    for (int i = 0; i < key_length; i++) {
        scanf("%d", &key[i]);
    }

    // Perform decryption with each possible key and calculate likelihood
    float likelihoods[MAX_PLAINTEXT_LENGTH] = {0};
    char plaintext[MAX_PLAINTEXT_LENGTH];
    for (int k = 0; k < ALPHABET_SIZE; k++) {
        for (int i = 0; i < key_length; i++) {
            key[i] = (key[i] + k) % ALPHABET_SIZE;
        }
        decrypt(ciphertext, key, key_length, ciphertext_length);
        likelihoods[k] = calculate_likelihood(ciphertext, ciphertext_length);
    }

    // Sort and print the top N plaintexts based on likelihood
    int top_n = 10;
    printf("\nTop %d possible plaintexts:\n", top_n);
    for (int i = 0; i < top_n; i++) {
        int max_index = 0;
        float max_likelihood = 0;
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if (likelihoods[j] > max_likelihood) {
                max_likelihood = likelihoods[j];
                max_index = j;
            }
        }
        likelihoods[max_index] = 0; // Mark as already printed
        for (int j = 0; j < ciphertext_length; j++) {
            plaintext[j] = ((ciphertext[j] - 'a') - (max_index + key[j % key_length]) + ALPHABET_SIZE) % ALPHABET_SIZE + 'a';
        }
        plaintext[ciphertext_length] = '\0';
        printf("%d. Likelihood: %.10f - %s\n", i + 1, max_likelihood, plaintext);
    }

    return 0;
}

