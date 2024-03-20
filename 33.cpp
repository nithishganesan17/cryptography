#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

#define BLOCK_SIZE 8 // DES block size is 64 bits (8 bytes)
#define KEY_SIZE 8   // DES key size is 56 bits (8 bytes)

// Function to handle errors
void handleErrors(void) {
    printf("Error occurred.\n");
    exit(EXIT_FAILURE);
}

// Function to perform DES encryption
void des_encrypt(const unsigned char *plaintext, unsigned char *ciphertext, const unsigned char *key) {
    DES_key_schedule key_schedule;
    DES_set_key_checked((const_DES_cblock *)key, &key_schedule);

    DES_ecb_encrypt((const_DES_cblock *)plaintext, (DES_cblock *)ciphertext, &key_schedule, DES_ENCRYPT);
}

// Function to perform DES decryption
void des_decrypt(const unsigned char *ciphertext, unsigned char *plaintext, const unsigned char *key) {
    DES_key_schedule key_schedule;
    DES_set_key_checked((const_DES_cblock *)key, &key_schedule);

    DES_ecb_encrypt((const_DES_cblock *)ciphertext, (DES_cblock *)plaintext, &key_schedule, DES_DECRYPT);
}

int main() {
    unsigned char key[KEY_SIZE] = {0x0E, 0x37, 0x6B, 0x4C, 0x55, 0x4E, 0x6D, 0x26}; // Example DES key (56 bits)
    unsigned char plaintext[BLOCK_SIZE] = "OpenSSL";                                      // Example plaintext
    unsigned char ciphertext[BLOCK_SIZE];                                                  // Buffer to store ciphertext
    unsigned char decrypted_text[BLOCK_SIZE];                                               // Buffer to store decrypted plaintext

    // Ensure the plaintext length is a multiple of BLOCK_SIZE
    int padded_len = BLOCK_SIZE * ((strlen((char *)plaintext) + BLOCK_SIZE - 1) / BLOCK_SIZE);

    // Perform encryption
    des_encrypt(plaintext, ciphertext, key);

    // Output ciphertext
    printf("Ciphertext: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    // Perform decryption
    des_decrypt(ciphertext, decrypted_text, key);

    // Output decrypted plaintext
    printf("Decrypted Text: %s\n", decrypted_text);

    return 0;
}

