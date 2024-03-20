#include <stdio.h>
#include <stdint.h>

#define NUM_ROUNDS 16

// Permutation table for initial key permutation
static const int initial_key_permutation_table[] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

// Permutation table for key compression
static const int key_compression_table[] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

// Circular left shift table
static const int left_shifts[NUM_ROUNDS] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

// Function to perform a circular left shift on a 28-bit value
uint32_t circular_left_shift(uint32_t value, int shift) {
    return ((value << shift) | (value >> (28 - shift))) & 0x0FFFFFFF;
}

// Function to generate 48-bit round keys from the initial 64-bit key
void generate_round_keys(uint64_t initial_key, uint64_t round_keys[NUM_ROUNDS]) {
    // Apply initial key permutation
    uint64_t permuted_key = 0;
    for (int i = 0; i < 56; i++) {
        permuted_key |= ((initial_key >> (64 - initial_key_permutation_table[i])) & 1) << (55 - i);
    }

    // Split the 56-bit permuted key into left and right halves
    uint32_t left = (uint32_t)(permuted_key >> 28) & 0x0FFFFFFF;
    uint32_t right = (uint32_t)(permuted_key & 0x0FFFFFFF);

    // Generate round keys
    for (int round = 0; round < NUM_ROUNDS; round++) {
        // Apply circular left shifts
        left = circular_left_shift(left, left_shifts[round]);
        right = circular_left_shift(right, left_shifts[round]);

        // Combine left and right halves
        uint64_t combined_key = ((uint64_t)left << 28) | right;

        // Apply key compression permutation
        uint64_t round_key = 0;
        for (int i = 0; i < 48; i++) {
            round_key |= ((combined_key >> (56 - key_compression_table[i])) & 1) << (47 - i);
        }

        // Store the round key
        round_keys[round] = round_key;
    }
}

int main() {
    // Example initial key (64 bits)
    uint64_t initial_key = 0x0000000000000000;

    // Array to store round keys
    uint64_t round_keys[NUM_ROUNDS];

    // Generate round keys
    generate_round_keys(initial_key, round_keys);

    // Output round keys
    printf("Round Keys:\n");
    for (int round = 0; round < NUM_ROUNDS; round++) {
        printf("Round %2d: 0x%012lx\n", round + 1, round_keys[round]);
    }

    return 0;
}

