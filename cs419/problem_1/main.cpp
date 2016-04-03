#include <stdio.h>
#include <openssl/evp.h>

unsigned char key[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH];

// Usage: cat words.txt | /Users/a5c/Library/Caches/CLion12/cmake/generated/6aca852e/6aca852e/Debug/problem1 | grep 8d20e5

// Adopted from: https://www.openssl.org/docs/manmaster/crypto/EVP_EncryptInit.html
int do_crypt(int do_encrypt) {
    /* Allow enough space in output buffer for additional block */
    int inlen = 0;
    int outlen;
    EVP_CIPHER_CTX ctx;
    /* Bogus key and IV: we'd normally set these from
     * another source.
     */
    unsigned char msg[] = "This is a top secret.";
    unsigned char iv[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    /* Don't set key or IV right away; we want to check lengths */
    EVP_CIPHER_CTX_init(&ctx);
    EVP_CipherInit_ex(&ctx, EVP_aes_128_cbc(), NULL, NULL, NULL, do_encrypt);
    OPENSSL_assert(EVP_CIPHER_CTX_key_length(&ctx) == 16);
    OPENSSL_assert(EVP_CIPHER_CTX_iv_length(&ctx) == 16);

    /* Now we can set key and IV */
    EVP_CipherInit_ex(&ctx, NULL, NULL, key, iv, do_encrypt);

    if (!EVP_CipherUpdate(&ctx, outbuf, &outlen, msg, 21)) {
        /* Error */
        EVP_CIPHER_CTX_cleanup(&ctx);
        return 0;
    }
    for (int i = 0; i < outlen; i++)
        printf("%02x", outbuf[i]);
    if (!EVP_CipherFinal_ex(&ctx, outbuf, &outlen)) {
        /* Error */
        EVP_CIPHER_CTX_cleanup(&ctx);
        return 0;
    }
    for (int i = 0; i < outlen; i++)
        printf("%02x", outbuf[i]);
    printf("\n");
    EVP_CIPHER_CTX_cleanup(&ctx);
    return 1;
}

int main(int argc, char *argv[]) {
    // Adopted from https://stackoverflow.com/questions/12252103/read-line-from-stdin-blocking
    char *line = NULL;
    size_t size;
    while (getline(&line, &size, stdin) != -1) {
        snprintf((char *) key, 17, "%s", line);
        printf("%s: ", key);
        do_crypt(1);
    }
    return 0;
}