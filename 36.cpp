#include <stdio.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to calculate the modular multiplicative inverse of a number
int modular_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

// Function to encrypt plaintext using the affine Caesar cipher
void affine_caesar_encrypt(char *plaintext, int a, int b) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            plaintext[i] = ((a * (plaintext[i] - base) + b) % ALPHABET_SIZE) + base;
        }
    }
}

// Function to decrypt ciphertext using the affine Caesar cipher
void affine_caesar_decrypt(char *ciphertext, int a, int b) {
    int a_inverse = modular_inverse(a, ALPHABET_SIZE);
    if (a_inverse == -1) {
        printf("Error: Modular inverse does not exist for the given key.\n");
        return;
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int decrypted_char = a_inverse * (ciphertext[i] - base - b);
            while (decrypted_char < 0) {
                decrypted_char += ALPHABET_SIZE;
            }
            plaintext[i] = (decrypted_char % ALPHABET_SIZE) + base;
        }
    }
}

int main() {
    char plaintext[] = "HelloWorld"; // Example plaintext
    int a = 5;                        // Example value of a
    int b = 8;                        // Example value of b

    // Encrypt the plaintext
    printf("Plaintext: %s\n", plaintext);
    affine_caesar_encrypt(plaintext, a, b);
    printf("Encrypted: %s\n", plaintext);

    // Decrypt the ciphertext
    affine_caesar_decrypt(plaintext, a, b);
    printf("Decrypted: %s\n", plaintext);

    return 0;
}

