#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Define English letter frequencies
double english_freq[26] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
    0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
    0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
    0.00978, 0.02360, 0.00150, 0.01974, 0.00074
};

// Function to calculate the score of a plaintext based on letter frequencies
double score_plaintext(char *plaintext) {
    int letter_count[26] = {0};
    int total_letters = 0;

    // Count the occurrences of each letter in the plaintext
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char c = tolower(plaintext[i]);
        if (isalpha(c)) {
            letter_count[c - 'a']++;
            total_letters++;
        }
    }

    // Calculate the score based on the frequency of each letter
    double score = 0.0;
    for (int i = 0; i < 26; i++) {
        double freq = (double)letter_count[i] / total_letters;
        score += freq * english_freq[i];
    }

    return score;
}

// Function to decrypt the ciphertext using a given key
void decrypt(char *ciphertext, char *key) {
    int len = strlen(ciphertext);

    printf("Possible plaintexts:\n");

    // Decrypt the ciphertext using the key
    for (int shift = 0; shift < 26; shift++) {
        printf("Key: %d\n", shift);
        printf("Plaintext: ");

        for (int i = 0; i < len; i++) {
            char c = ciphertext[i];

            if (isalpha(c)) {
                char decrypted_char = 'a' + (tolower(c) - 'a' - shift + 26) % 26;
                if (isupper(c)) decrypted_char = toupper(decrypted_char);
                printf("%c", decrypted_char);
            } else {
                printf("%c", c);
            }
        }

        printf("\n");
    }
}

int main() {
    char ciphertext[1000];
    char key[26];
    int top_plaintexts = 10;

    // Input the ciphertext
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    // Remove newline character
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    // Decrypt the ciphertext using a key
    decrypt(ciphertext, key);

    return 0;
}

