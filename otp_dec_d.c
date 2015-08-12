#include "cipher_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include "server_lib.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"


int portNumber = 8080;
char buffer[BUFSIZ];
int keyBuffer[BUFSIZ];
int msgBuffer[BUFSIZ];
int resultBuffer[BUFSIZ];

const char *usage = "Usage: otd_dec_d [port #]\n";

void *handleClientDecryption(void *_clientFd) {
    int clientFd = (int) _clientFd;
    ssize_t receiveLength;
    ssize_t sendSuccess;
    size_t keyLength;
    size_t msgLength;

    while (1) {
        // Read the key and msg lengths
        receiveLength = recv(clientFd, buffer, sizeof(int) * 2, 0);
        if (!receiveLength)
            return NULL;
        keyLength = (size_t) buffer[0];
        msgLength = (size_t) buffer[1];
        receiveLength = 0;
        while (receiveLength < keyLength)
            receiveLength += recv(clientFd, buffer + receiveLength, keyLength - receiveLength, 0);
        buffer[keyLength] = '\0';
        encode(keyBuffer, buffer);
        receiveLength = 0;
        while (receiveLength < msgLength)
            receiveLength += recv(clientFd, buffer + receiveLength, msgLength - receiveLength, 0);
        buffer[msgLength] = '\0';
        encode(msgBuffer, buffer);
        decrypt(resultBuffer, msgBuffer, keyBuffer, (int) msgLength);
        decode(buffer, resultBuffer, (int) msgLength);
        sendSuccess = send(clientFd, buffer, msgLength, 0);
        if (!sendSuccess)
            return NULL;
    }

    return NULL;
}

int main(int argc, char *argv[]) {

    /* --- Read port from arguments or print usage -- */
    if (argc < 2 || atoi(argv[1]) == 0) {
        printf("%s", usage);
        return 1;
    } else {
        portNumber = atoi(argv[1]);
    }

    return startServer("otp_dec_d", portNumber, handleClientDecryption);
}

#pragma clang diagnostic pop
