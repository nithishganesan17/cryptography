#include<stdio.h>

#include<ctype.h>

int main() {

    char text[50]="hello everyone";
    char ch;

    int key=1;
    // Visiting character by character.

    for (int i = 0; text[i] != '\0'; ++i) {

        ch = text[i];
        // Check for valid characters.
        if (isalnum(ch)) {

            //Lowercase characters.
            if (islower(ch)) {
                ch = (ch - 'a' + key) % 26 + 'a';
            }
            // Uppercase characters.
            if (isupper(ch)) {
                ch = (ch - 'A' + key) % 26 + 'A';
            }

            // Numbers.
            if (isdigit(ch)) {
                ch = (ch - '0' + key) % 10 + '0';
            }
        }
        else {
            printf("Invalid Message");
        }
        text[i] = ch;

    }

    printf("Encrypted message: %s", text);

    return 0;
}

