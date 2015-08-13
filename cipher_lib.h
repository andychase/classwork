#ifndef PROJECT4_CIPHER_LIB_H
#define PROJECT4_CIPHER_LIB_H
void otp_encode(int *buffer, char *inputString);

void otp_decode(char *buffer, int *inputArray, int size);

void otp_encrypt(int *buffer, int *text, int *key, int size);

void otp_decrypt(int *buffer, int *text, int *key, int size);
void selfTest();

#endif //PROJECT4_CIPHER_LIB_H
