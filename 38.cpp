#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ALPHABET_SIZE 26

// Function to find the modular multiplicative inverse of a number
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

// Function to calculate the determinant of a 2x2 matrix
int determinant_2x2(int mat[2][2]) {
    return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

// Function to calculate the modular determinant of a 2x2 matrix
int mod_determinant_2x2(int mat[2][2], int mod) {
    return ((mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0] + mod)) % mod;
}

// Function to calculate the inverse of a 2x2 matrix
void inverse_2x2(int mat[2][2], int mod, int adj[2][2]) {
    int det = mod_inverse(determinant_2x2(mat), mod);
    if (det == -1) {
        printf("Error: Inverse does not exist.\n");
        exit(EXIT_FAILURE);
    }
    adj[0][0] = (mat[1][1] * det) % mod;
    adj[0][1] = (-mat[0][1] * det) % mod;
    adj[1][0] = (-mat[1][0] * det) % mod;
    adj[1][1] = (mat[0][0] * det) % mod;
}

// Function to calculate the modular inverse of a 2x2 matrix
void mod_inverse_2x2(int mat[2][2], int mod, int inv[2][2]) {
    int det_inv = mod_inverse(determinant_2x2(mat), mod);
    if (det_inv == -1) {
        printf("Error: Inverse does not exist.\n");
        exit(EXIT_FAILURE);
    }

    int adj[2][2];
    inverse_2x2(mat, mod, adj);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inv[i][j] = (adj[i][j] * det_inv) % mod;
            if (inv[i][j] < 0) {
                inv[i][j] += mod;
            }
        }
    }
}

// Function to decrypt ciphertext using the Hill cipher
void hill_decrypt(char *ciphertext, int key[2][2], int mod) {
    int len = strlen(ciphertext);
    int decrypted[len];
    int inv_key[2][2];
    mod_inverse_2x2(key, mod, inv_key);

    for (int i = 0; i < len; i += 2) {
        int c1 = ciphertext[i] - 'A';
        int c2 = ciphertext[i + 1] - 'A';
        decrypted[i] = (inv_key[0][0] * c1 + inv_key[0][1] * c2) % mod;
        decrypted[i + 1] = (inv_key[1][0] * c1 + inv_key[1][1] * c2) % mod;
    }

    for (int i = 0; i < len; i++) {
        decrypted[i] += 'A';
        decrypted[i] %= ALPHABET_SIZE;
        ciphertext[i] = decrypted[i];
    }
}

int main() {
    char ciphertext[] = "BN"; // Example ciphertext
    int plaintext[] = {0, 13}; // Corresponding known plaintext
    int key[2][2] = {{7, 8}, {11, 11}}; // Example key matrix
    int mod = ALPHABET_SIZE; // Modulus (size of the alphabet)

    // Decrypt the ciphertext
    hill_decrypt(ciphertext, key, mod);

    // Print the decrypted plaintext
    printf("Decrypted plaintext: %s\n", ciphertext);

    return 0;
}

