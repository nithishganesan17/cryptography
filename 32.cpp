#include <stdio.h>
#include <stdlib.h>
#include <openssl/dsa.h>
#include <openssl/err.h>

#define MESSAGE "Hello, World!"

// Function to handle errors
void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
}

// Function to generate DSA key pair
DSA* generateDSAKeyPair(void) {
    DSA *dsa = NULL;
    dsa = DSA_new();
    if (!dsa) {
        handleErrors();
    }
    DSA_generate_parameters_ex(dsa, 1024, NULL, 0, NULL, NULL, NULL);
    if (!DSA_generate_key(dsa)) {
        handleErrors();
    }
    return dsa;
}

// Function to sign a message using DSA
DSA_SIG* signMessageDSA(const unsigned char *msg, size_t len, DSA *dsa) {
    DSA_SIG *sig;
    sig = DSA_do_sign(msg, len, dsa);
    if (!sig) {
        handleErrors();
    }
    return sig;
}

// Function to verify a signature using DSA
int verifySignatureDSA(const unsigned char *msg, size_t len, DSA_SIG *sig, DSA *dsa) {
    return DSA_do_verify(msg, len, sig, dsa);
}

int main() {
    DSA *dsa = generateDSAKeyPair();
    DSA_SIG *signature1, *signature2;
    const unsigned char *msg = (const unsigned char *)MESSAGE;
    size_t len = strlen(MESSAGE);

    // Signing the message for the first time
    signature1 = signMessageDSA(msg, len, dsa);
    if (!signature1) {
        printf("Failed to sign message.\n");
        return 1;
    }

    // Verifying the first signature
    int verification1 = verifySignatureDSA(msg, len, signature1, dsa);
    if (verification1 != 1) {
        printf("First signature verification failed.\n");
        return 1;
    }

    // Signing the message for the second time
    signature2 = signMessageDSA(msg, len, dsa);
    if (!signature2) {
        printf("Failed to sign message.\n");
        return 1;
    }

    // Verifying the second signature
    int verification2 = verifySignatureDSA(msg, len, signature2, dsa);
    if (verification2 != 1) {
        printf("Second signature verification failed.\n");
        return 1;
    }

    // Print the signatures
    printf("Signature 1: ");
    for (int i = 0; i < BN_num_bytes(signature1->r); i++) {
        printf("%02x", BN_get_byte(signature1->r, i));
    }
    printf("\n");

    printf("Signature 2: ");
    for (int i = 0; i < BN_num_bytes(signature2->r); i++) {
        printf("%02x", BN_get_byte(signature2->r, i));
    }
    printf("\n");

    // Freeing resources
    DSA_free(dsa);
    DSA_SIG_free(signature1);
    DSA_SIG_free(signature2);

    return 0;
}

