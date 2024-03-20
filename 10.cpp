#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char playfairMatrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};


void removeNonAlphabetic(char *message) {
    int i, j = 0;
    for (i = 0; message[i] != '\0'; ++i) {
        if (isalpha(message[i])) {
            message[j++] = toupper(message[i]);
        }
    }
    message[j] = '\0';
}

void findPositions(char a, char b, int *row_a, int *col_a, int *row_b, int *col_b) {
    int i, j;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            if (playfairMatrix[i][j] == a) {
                *row_a = i;
                *col_a = j;
            }
            if (playfairMatrix[i][j] == b) {
                *row_b = i;
                *col_b = j;
            }
        }
    }
}

// Function to encrypt the message using the Playfair cipher
void encrypt(char *message) {
    removeNonAlphabetic(message);

    int len = strlen(message);
    int i;
    for (i = 0; i < len; i += 2) {
        char a = message[i];
        char b = (i + 1 < len) ? message[i + 1] : 'X'; // 'X' is used for padding if necessary
        int row_a, col_a, row_b, col_b;

        findPositions(a, b, &row_a, &col_a, &row_b, &col_b);

        // Same row
        if (row_a == row_b) {
            printf("%c%c", playfairMatrix[row_a][(col_a + 1) % SIZE], playfairMatrix[row_b][(col_b + 1) % SIZE]);
        }
        // Same column
        else if (col_a == col_b) {
            printf("%c%c", playfairMatrix[(row_a + 1) % SIZE][col_a], playfairMatrix[(row_b + 1) % SIZE][col_b]);
        }
        // Rectangle
        else {
            printf("%c%c", playfairMatrix[row_a][col_b], playfairMatrix[row_b][col_a]);
        }
    }
    printf("\n");
}

int main() {
    char message[] = "Must see you over Cadogan West. Coming at once.";

    printf("Original message: %s\n", message);
    printf("Encrypted message: ");
    encrypt(message);

    return 0;
}
