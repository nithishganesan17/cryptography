#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Function to encrypt plaintext using the one-time pad Vigenère cipher
void encrypt(char *plaintext, const int *key) {
    int key_index = 0;
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            plaintext[i] = ((plaintext[i] - base + key[key_index]) % ALPHABET_SIZE) + base;
            key_index = (key_index + 1) % strlen((char *)key);
        }
    }
}

// Function to decrypt ciphertext using the one-time pad Vigenère cipher
void decrypt(char *ciphertext, const int *key) {
    int key_index = 0;
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            ciphertext[i] = ((ciphertext[i] - base - key[key_index] + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
            key_index = (key_index + 1) % strlen((char *)key);
        }
    }
}

int main() {
    char plaintext[] = "HelloWorld"; // Example plaintext
    int key[] = {3, 19, 5};          // Example key

    // Ensure key length is at least as long as plaintext
    if (strlen(plaintext) > strlen((char *)key)) {
        printf("Error: Key length must be at least as long as plaintext.\n");
        return 1;
    }

    // Encrypt the plaintext
    printf("Plaintext: %s\n", plaintext);
    encrypt(plaintext, key);
    printf("Encrypted: %s\n", plaintext);

    // Decrypt the ciphertext
    decrypt(plaintext, key);
    printf("Decrypted: %s\n", plaintext);

    return 0;
}

