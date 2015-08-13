/*
 * Refernences:
 * - https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "cipher_lib.h"
#include "server_lib.h"

char buffer[BUFSIZ];
char msgBuffer[BUFSIZ];
char keyBuffer[BUFSIZ];
const char *usage = "Usage: otd_enc msg key [enc port #]\n";

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("%s", usage);
        return 1;
    }
    int port = atoi(argv[3]);

    size_t msgBytesRead = 1;
    size_t keyBytesRead = 1;
    FILE *msgFile = fopen(argv[1], "r");
    FILE *keyFile = fopen(argv[2], "r");
    {
        fseek(msgFile, 0L, SEEK_END);
        fseek(keyFile, 0L, SEEK_END);
        long msgSize = ftell(msgFile);
        long keySize = ftell(keyFile);
        fseek(msgFile, 0L, SEEK_SET);
        fseek(keyFile, 0L, SEEK_SET);
        if (msgSize != keySize) {
            printf("Key size does not match message size");
            return 1;
        }
    }

    if (msgFile && keyFile) {
        int socket = openConnectSocket(port);
        while (msgBytesRead && keyBytesRead) {
            msgBytesRead = fread(buffer, 1, BUFSIZ-1, msgFile);
            keyBytesRead = fread(buffer, 1, BUFSIZ-1, keyFile);

            if (msgBytesRead && keyBytesRead) {
                handleServerConnection(socket, 1, keyBuffer, msgBuffer, buffer, (size_t) fmin(BUFSIZ-1, msgBytesRead));
                buffer[BUFSIZ-1] = '\0';
                printf("%s", buffer);
            }
        }
    } else {
        perror("Error opening msgFile or keyFile");
    }
    return 0;
}
