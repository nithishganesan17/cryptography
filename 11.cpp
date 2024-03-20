#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 2

int key[SIZE][SIZE] = {{9, 4}, {5, 7}};

void removeNonAlphabetic(char *message) {
    int i, j = 0;
    for (i = 0; message[i] != '\0'; ++i) {
        if (isalpha(message[i])) {
            message[j++] = toupper(message[i]);
        }
    }
    message[j] = '\0';
}

void encrypt(char *message) {
    removeNonAlphabetic(message);
    
    int len = strlen(message);
    int i, j, k, sum;
    int ciphertext[len];
    int numeric[len];
    for (i = 0; i < len; ++i) {
        numeric[i] = message[i] - 'A';
    }

    for (i = 0; i < len; i += 2) {
        int pair[2] = {numeric[i], (i + 1 < len) ? numeric[i + 1] : 23}; 
        int result[2] = {0, 0};

        
        for (j = 0; j < SIZE; ++j) {
            sum = 0;
            for (k = 0; k < SIZE; ++k) {
                sum += key[j][k] * pair[k];
            }
            result[j] = sum % 26;
        }

        
        for (j = 0; j < SIZE; ++j) {
            ciphertext[i + j] = result[j];
        }
    }

    // Print the encrypted message
    printf("Encrypted message: ");
    for (i = 0; i < len; ++i) {
        printf("%c", ciphertext[i] + 'A');
    }
    printf("\n");
}

int main() {
    char message[] = "meet me at the usual place at ten rather than eight oclock";

    printf("Original message: %s\n", message);
    encrypt(message);

    return 0;
}
