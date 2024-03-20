#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 136
#define STATE_SIZE 25
#define HASH_SIZE 32

#define ROTL64(x, n) (((x) << (n)) | ((x) >> (64 - (n))))

const uint64_t RC[24] = {
    0x0000000000000001ULL, 0x0000000000008082ULL, 0x800000000000808aULL,
    0x8000000080008000ULL, 0x000000000000808bULL, 0x0000000080000001ULL,
    0x8000000080008081ULL, 0x8000000000008009ULL, 0x000000000000008aULL,
    0x0000000000000088ULL, 0x0000000080008009ULL, 0x000000008000000aULL,
    0x000000008000808bULL, 0x800000000000008bULL, 0x8000000000008089ULL,
    0x8000000000008003ULL, 0x8000000000008002ULL, 0x8000000000000080ULL,
    0x000000000000800aULL, 0x800000008000000aULL, 0x8000000080008081ULL,
    0x8000000000008080ULL, 0x0000000080000001ULL, 0x8000000080008008ULL
};

void sha3(const uint8_t *message, uint64_t message_size, uint8_t *hash) {
    uint64_t state[STATE_SIZE] = {0};

    uint64_t block_count = (message_size + BLOCK_SIZE - 1) / BLOCK_SIZE;

    for (uint64_t block = 0; block < block_count; block++) {
        for (uint64_t i = 0; i < BLOCK_SIZE / 8; i++) {
            uint64_t word = 0;
            for (uint64_t j = 0; j < 8; j++) {
                uint64_t byte_index = block * BLOCK_SIZE + i * 8 + j;
                if (byte_index < message_size) {
                    word |= (uint64_t)message[byte_index] << (j * 8);
                }
            }
            state[i] ^= word;
        }

        uint64_t round = 0;
        while (round < 24) {
            // Theta step
            uint64_t C[5], D[5];
            for (uint64_t x = 0; x < 5; x++) {
                C[x] = state[x] ^ state[x + 5] ^ state[x + 10] ^ state[x + 15] ^ state[x + 20];
            }
            for (uint64_t x = 0; x < 5; x++) {
                D[x] = C[(x + 4) % 5] ^ ROTL64(C[(x + 1) % 5], 1);
            }
            for (uint64_t x = 0; x < 5; x++) {
                for (uint64_t y = 0; y < 25; y += 5) {
                    state[y + x] ^= D[x];
                }
            }

            // Rho and Pi steps
            uint64_t x = 1, y = 0;
            uint64_t current = state[1];
            for (uint64_t t = 0; t < 24; t++) {
                uint64_t temp = x;
                x = y;
                y = (2 * temp + 3 * y) % 5;
                temp = state[(y * 5) + x];
                state[(y * 5) + x] = ROTL64(current, ((t + 1) * (t + 2)) / 2);
                current = temp;
            }

            // Chi step
            for (y = 0; y < 5; y++) {
                for (x = 0; x < 5; x++) {
                    C[x] = state[(y * 5) + x];
                }
                for (x = 0; x < 5; x++) {
                    state[(y * 5) + x] ^= (~C[(x + 1) % 5]) & C[(x + 2) % 5];
                }
            }

            // Iota step
            state[0] ^= RC[round];
            round++;
        }
    }

    // Copy hash result
    memcpy(hash, state, HASH_SIZE);
}

int main() {
    // Example usage
    const uint8_t message[] = "Hello, SHA-3!";
    uint8_t hash[HASH_SIZE];

    // Compute SHA-3 hash
    sha3(message, strlen((const char *)message), hash);

    // Print the hash
    printf("SHA-3 hash: ");
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}
