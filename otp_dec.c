/*
 * References:
 * - https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
 */
#include <stdio.h>
#include <stdlib.h>
#include "server_lib.h"

char buffer[BUFSIZ];
char msgBuffer[BUFSIZ];
char keyBuffer[BUFSIZ];
const char *usage = "Usage: otd_dec msg key [enc port #]\n";

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("%s", usage);
        return 1;
    }
    int port = atoi(argv[3]);

    size_t msgBytesRead;
    size_t keyBytesRead;
    FILE *msgFile = fopen(argv[1], "r");
    FILE *keyFile = fopen(argv[2], "r");
    if (msgFile && keyFile) {
        {
            fseek(msgFile, 0L, SEEK_END);
            fseek(keyFile, 0L, SEEK_END);
            long msgSize = ftell(msgFile);
            long keySize = ftell(keyFile);
            fseek(msgFile, 0L, SEEK_SET);
            fseek(keyFile, 0L, SEEK_SET);
            if (keySize < msgSize) {
                printf("Key size is too short. Must be %d, but is %d", (int) msgSize, (int) keySize);
                return 1;
            }
        }

        size_t receivedData;
        int socket = openConnectSocket(port);
        if (socket < 1) {
            printf("Error connecting to encryption server.\n");
            return 1;
        }
        while (1) {
            msgBytesRead = fread(msgBuffer, 1, BUFSIZ - 1, msgFile);
            if (!msgBytesRead)
                break;
            if (msgBuffer[msgBytesRead - 1] == '\n') {
                msgBuffer[msgBytesRead - 1] = '\0';
                msgBytesRead -= 1;
            }
            keyBytesRead = fread(keyBuffer, 1, msgBytesRead, keyFile);

            if (keyBytesRead) {
                receivedData = handleServerConnection(socket, 0, keyBuffer, msgBuffer, buffer, msgBytesRead);
                if (msgBytesRead != receivedData) {
                    printf("Server terminated the connection");
                    return 1;
                }
                buffer[msgBytesRead] = '\0';
                printf("%s", buffer);
            }
        }
        printf("\n");
    } else {
        snprintf(buffer, BUFSIZ, "Error opening msgFile: %s or keyFile: %s", argv[1], argv[2]);
        perror(buffer);
    }
    return 0;
}
