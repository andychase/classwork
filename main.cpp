#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>

#define BYTES 3

bool same(unsigned char md_value1[EVP_MAX_MD_SIZE], unsigned char md_value2[EVP_MAX_MD_SIZE]) {
    for (int i = 0; i < BYTES; i++)
        if (md_value1[i] != md_value2[i])
            return false;
    return true;
}

int main(int argc, char *argv[]) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    char mess1[] = "Test Message\n";
    char mess2[32];
    unsigned char md_value1[EVP_MAX_MD_SIZE];
    unsigned char md_value2[EVP_MAX_MD_SIZE];
    int md_len;
    srand((unsigned int) time(NULL));

    OpenSSL_add_all_digests();

    md = EVP_get_digestbyname("sha256");

    if (!md) {
        printf("Unknown message digest %s\n", argv[1]);
        exit(1);
    }

    mdctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, mess1, strlen(mess1));
    EVP_DigestFinal_ex(mdctx, md_value1, (unsigned int *) &md_len);
    EVP_MD_CTX_destroy(mdctx);

    printf("Rounds to find a 3 byte hash collision \n");
    for (int t = 0; t < 70; t++) {

        long nonce = rand() + (rand() * 20720703);
        int rounds = 0;

        do {
            snprintf(mess2, 32, "%lu", nonce);
            mdctx = EVP_MD_CTX_create();
            EVP_DigestInit_ex(mdctx, md, NULL);
            EVP_DigestUpdate(mdctx, mess2, strlen(mess2));
            EVP_DigestFinal_ex(mdctx, md_value2, (unsigned int *) &md_len);
            EVP_MD_CTX_destroy(mdctx);
            nonce++;
            rounds++;
        } while (!same(md_value1, md_value2));

        printf("Rounds: %d\n", rounds);
    }

    /* Call this once before exit. */
    EVP_cleanup();
    exit(0);
}