#include <stdio.h>
#include <stdlib.h>
#include <math.h>
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1; 
        base = (base * base) % mod;
    }
    return result;
}
long long encryptCharacter(int character, long long e, long long n) {
    return modExp(character, e, n);
}

int main() {
    
    long long e = 65537;
    long long n = 281474976710597; 

   
    char message[] = "HELLO";

    
    printf("Encrypted message: ");
    for (int i = 0; message[i] != '\0'; ++i) {
        if (message[i] >= 'A' && message[i] <= 'Z') {
            int character = message[i] - 'A'; 
            long long encryptedChar = encryptCharacter(character, e, n);
            printf("%lld ", encryptedChar);
        }
    }
    printf("\n");

    return 0;
}
