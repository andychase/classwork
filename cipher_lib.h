#ifndef PROJECT4_CIPHER_LIB_H
#define PROJECT4_CIPHER_LIB_H
void encode(int *buffer, char *inputString);

void decode(char *buffer, int *inputArray, int size);

void encrypt(int *buffer, int *text, int *key, int size);

void decrypt(int *buffer, int *text, int *key, int size);
void selfTest();

#endif //PROJECT4_CIPHER_LIB_H
