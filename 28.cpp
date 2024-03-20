#include <stdio.h>
#include <stdint.h>

// Define constants for block sizes
#define BLOCK_SIZE_64  8
#define BLOCK_SIZE_128 16

// Function to left shift a byte array by one bit
void leftShiftOneBit(uint8_t *data, int size) {
    int i;
    uint8_t carry = 0;
    for (i = size - 1; i >= 0; i--) {
        uint8_t nextCarry = (data[i] & 0x80) ? 1 : 0;
        data[i] = (data[i] << 1) | carry;
        carry = nextCarry;
    }
}

// Function to XOR two byte arrays
void xorBytes(uint8_t *a, uint8_t *b, int size) {
    for (int i = 0; i < size; i++) {
        a[i] ^= b[i];
    }
}

// Function to generate subkeys for CMAC
void generateSubkeys(uint8_t *key, int keySize, uint8_t *subkeys) {
    uint8_t zeroBlock[BLOCK_SIZE_128] = {0}; // Assuming maximum block size

    // Apply block cipher to zero block
    // (In actual implementation, you would use your block cipher function here)
    // For this example, we'll just copy zeroBlock to result
    uint8_t result[BLOCK_SIZE_128];
    for (int i = 0; i < keySize; i++) {
        result[i] = zeroBlock[i];
    }

    // Generate subkeys
    for (int i = 0; i < keySize; i++) {
        // Left shift
        leftShiftOneBit(result, keySize);

        // XOR with constant
        if (result[0] & 0x80) { // Check MSB of result
            // XOR with constant (depends on block size)
            if (keySize == BLOCK_SIZE_64) {
                xorBytes(result, key, keySize);
            } else if (keySize == BLOCK_SIZE_128) {
                // Define constant for 128-bit block size
                uint8_t const128[BLOCK_SIZE_128] = {0x87, 0x0, 0x0, 0x0,
                                                      0x0,  0x0, 0x0, 0x0,
                                                      0x0,  0x0, 0x0, 0x0,
                                                      0x0,  0x0, 0x0, 0x0};
                xorBytes(result, const128, keySize);
            }
        }

        // Copy subkey
        for (int j = 0; j < keySize; j++) {
            subkeys[i * keySize + j] = result[j];
        }
    }
}

int main() {
    // Example usage
    uint8_t key[BLOCK_SIZE_128] = {0}; // Assume a 128-bit key
    uint8_t subkeys[BLOCK_SIZE_128 * 2]; // Store subkeys

    // Generate subkeys
    generateSubkeys(key, BLOCK_SIZE_128, subkeys);

    // Print subkeys
    printf("Subkeys:\n");
    for (int i = 0; i < BLOCK_SIZE_128 * 2; i++) {
        printf("%02x ", subkeys[i]);
    }
    printf("\n");

    return 0;
}
