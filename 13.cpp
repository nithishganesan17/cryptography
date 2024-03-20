#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100

void encrypt(char *message, int key[][MAX_SIZE], int keySize) {
    int i, j, k, len, sum;

    len = strlen(message);

    int encrypted[len];

    for (i = 0; i < len; i += keySize) {
        for (j = 0; j < keySize; j++) {
            sum = 0;
            for (k = 0; k < keySize; k++) {
                sum += key[j][k] * (message[i + k] - 'a');
            }
            encrypted[i + j] = sum % 26;
        }
    }

    // Print the encrypted message
    printf("Encrypted Message: ");
    for (i = 0; i < len; i++) {
        printf("%c", encrypted[i] + 'a');
    }
    printf("\n");
}

// Main function
int main() {
    char message[MAX_SIZE];
    int key[MAX_SIZE][MAX_SIZE];
    int keySize, i, j;

    // Input the message to be encrypted
    printf("Enter the message to be encrypted: ");
    fgets(message, MAX_SIZE, stdin);

    // Remove newline character
    message[strcspn(message, "\n")] = 0;

    // Input the size of the key matrix
    printf("Enter the size of the key matrix: ");
    scanf("%d", &keySize);

    // Input the key matrix
    printf("Enter the key matrix elements: \n");
    for (i = 0; i < keySize; i++) {
        for (j = 0; j < keySize; j++) {
            scanf("%d", &key[i][j]);
        }
    }

    // Encrypt the message using the Hill Cipher
    encrypt(message, key, keySize);

    return 0;
}

