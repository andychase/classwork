#include <stdlib.h>
#include <stdio.h>
#include "server_lib.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"


int portNumber = 8080;
char buffer[BUFSIZ];
int keyBuffer[BUFSIZ];
int msgBuffer[BUFSIZ];
int resultBuffer[BUFSIZ];

const char *usage = "Usage: otd_dec_d [port #]\n";

void handleClientDecryption(int clientFd) {
    int encryptionMode = 0; /* Decryption Mode set */
    handleClient(clientFd, encryptionMode, buffer, resultBuffer, keyBuffer, msgBuffer);
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
