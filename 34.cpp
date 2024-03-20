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
void des_encrypt(const unsigned char *plaintext, unsigned char *ciphertext, const unsigned char *key, DES_cblock *iv, int mode) {
    DES_key_schedule key_schedule;
    DES_set_key_checked((const_DES_cblock *)key, &key_schedule);

    if (mode == DES_ENCRYPT)
        DES_ecb_encrypt((const_DES_cblock *)plaintext, (DES_cblock *)ciphertext, &key_schedule, mode);
    else
        DES_ncbc_encrypt(plaintext, ciphertext, BLOCK_SIZE, &key_schedule, iv, mode);
}

// Function to perform DES decryption
void des_decrypt(const unsigned char *ciphertext, unsigned char *plaintext, const unsigned char *key, DES_cblock *iv, int mode) {
    DES_key_schedule key_schedule;
    DES_set_key_checked((const_DES_cblock *)key, &key_schedule);

    if (mode == DES_ENCRYPT)
        DES_ecb_encrypt((const_DES_cblock *)ciphertext, (DES_cblock *)plaintext, &key_schedule, mode);
    else
        DES_ncbc_encrypt(ciphertext, plaintext, BLOCK_SIZE, &key_schedule, iv, mode);
}

int main() {
    unsigned char key[KEY_SIZE] = {0x0E, 0x37, 0x6B, 0x4C, 0x55, 0x4E, 0x6D, 0x26}; // Example DES key (56 bits)
    unsigned char plaintext[] = "Hello, world!"; // Example plaintext
    unsigned char ciphertext[BLOCK_SIZE];        // Buffer to store ciphertext
    unsigned char decrypted_text[BLOCK_SIZE];     // Buffer to store decrypted plaintext
    DES_cblock iv;                               // Initialization vector for CBC mode

    // Initialize IV for CBC mode
    RAND_bytes(iv, sizeof(iv));

    // Perform ECB encryption
    des_encrypt(plaintext, ciphertext, key, NULL, DES_ENCRYPT);
    printf("ECB Encrypted: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    // Perform ECB decryption
    des_decrypt(ciphertext, decrypted_text, key, NULL, DES_DECRYPT);
    printf("ECB Decrypted: %s\n", decrypted_text);

    // Perform CBC encryption
    des_encrypt(plaintext, ciphertext, key, &iv, DES_ENCRYPT);
    printf("CBC Encrypted: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    // Perform CBC decryption
    des_decrypt(ciphertext, decrypted_text, key, &iv, DES_DECRYPT);
    printf("CBC Decrypted: %s\n", decrypted_text);

    // Perform CFB encryption (using previous ciphertext as IV)
    des_encrypt(plaintext, ciphertext, key, &iv, DES_ENCRYPT);
    printf("CFB Encrypted: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    // Perform CFB decryption (using previous ciphertext as IV)
    des_decrypt(ciphertext, decrypted_text, key, &iv, DES_DECRYPT);
    printf("CFB Decrypted: %s\n", decrypted_text);

    return 0;
}

