#include <string.h>
#include <assert.h>
#include "cipher_lib.h"

#define STARTCHAR (int) 'A'
#define CHARSET 27

/* Encode char to 0-27 */
int encodeChar(char inputChar) {
    if (inputChar == ' ') {
        return CHARSET - 1;
    } else {
        int result;
        result = inputChar - STARTCHAR;
        if (result < CHARSET && result >= 0) {
            return result;
        } else {
            return -1;
        }
    }
}

/* Decode 0-27 to char */
char decodeChar(int inputInt) {
    if (inputInt == CHARSET - 1) {
        return ' ';
    } else {
        return (char) (inputInt + STARTCHAR);
    }
}

void otp_encode(int *buffer, char *inputString) {
    int i;
    int length = (int) strlen(inputString);
    for (i = 0; i < length; i++) {
        buffer[i] = encodeChar(inputString[i]);
    }
}

void otp_decode(char *buffer, int *inputArray, int size) {
    int i;
    for (i = 0; i < size; i++) {
        buffer[i] = decodeChar(inputArray[i]);
    }
    buffer[size] = '\0';
}

/* Encrypts text using buffer */
void otp_encrypt(int *buffer, int *text, int *key, int size) {
    int i;
    for (i = 0; i < size; i++) {
        buffer[i] = (text[i] + key[i]) % CHARSET;
    }
}

/* Decrypts text using buffer */
void otp_decrypt(int *buffer, int *text, int *key, int size) {
    int i;
    int result;
    for (i = 0; i < size; i++) {
        result = (text[i] - key[i]) % CHARSET;
        if (result >= 0)
            buffer[i] = result;
        else
            buffer[i] = result + CHARSET;
    }
}

/* A unit test function which is not linked anywhere currently */
void __unused selfTest() {
    int buffer[5];
    int inputMsg[] = {7, 4, 11, 11, 14};
    int inputKey[] = {23, 12, 2, 10, 11};
    otp_encrypt(buffer, inputMsg, inputKey, 5);
    assert(buffer[0] == 3);
    assert(buffer[1] == 16);
    assert(buffer[2] == 13);
    assert(buffer[3] == 21);
    assert(buffer[4] == 25);
    otp_decrypt(buffer, buffer, inputKey, 5);
    assert(buffer[0] == inputMsg[0]);
    assert(buffer[1] == inputMsg[1]);
    assert(buffer[2] == inputMsg[2]);
    assert(buffer[3] == inputMsg[3]);
    assert(buffer[4] == inputMsg[4]);
    otp_encode(buffer, "H LLO");
    assert(buffer[0] == inputMsg[0]);
    assert(buffer[1] == 26);
    assert(buffer[2] == inputMsg[2]);
    assert(buffer[3] == inputMsg[3]);
    assert(buffer[4] == inputMsg[4]);
    char buffer2[5];
    otp_decode(buffer2, inputMsg, 5);
    assert(strstr(buffer2, "HELLO"));
}
