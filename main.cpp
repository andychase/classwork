#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>
#include <unordered_set>
#include <string>


int main(int argc, char *argv[]) {
    std::unordered_set<std::string> myset;
    std::string my_value_copy;
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    char mess[32];
    unsigned char md_value[EVP_MAX_MD_SIZE];
    int md_len;
    srand((unsigned int) time(NULL));


    OpenSSL_add_all_digests();

    md = EVP_get_digestbyname("sha256");

    if (!md) {
        printf("Unknown message digest %s\n", argv[1]);
        exit(1);
    }

    printf("Rounds to find a 3 byte hash collision \n");
    for (int t = 0; t < 1000; t++) {
        unsigned int rounds = 0;
        long nonce = rand() + (rand() * 20720703);
        myset.clear();
        do {

            snprintf(mess, 32, "%lu", nonce);
            mdctx = EVP_MD_CTX_create();
            EVP_DigestInit_ex(mdctx, md, NULL);
            EVP_DigestUpdate(mdctx, mess, strlen(mess));
            EVP_DigestFinal_ex(mdctx, md_value, (unsigned int *) &md_len);
            EVP_MD_CTX_destroy(mdctx);
            rounds++;
            nonce++;
            my_value_copy.clear();
            my_value_copy += md_value[0];
            my_value_copy += md_value[1];
            my_value_copy += md_value[2];

            if (myset.count(my_value_copy) == 1)
                break;
            myset.insert(my_value_copy);

        } while (true);

        printf("Rounds: %d\n", rounds);
    }

    /* Call this once before exit. */
    EVP_cleanup();
    exit(0);
}