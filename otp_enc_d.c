#include <stdlib.h>
#include <stdio.h>
#include "server_lib.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"


int portNumber = 8080;

const char *usage = "Usage: otd_enc_d [port #]\n";

void * handleClientEncryption(void* _clientFd) {
    int clientFd = (int) _clientFd;

}

int main(int argc, char *argv[]) {

    /* --- Read port from arguments or print usage -- */
    if (argc < 2 || atoi(argv[1]) == 0) {
        printf("%s", usage);
        return 1;
    } else {
        portNumber = atoi(argv[1]);
    }

    return startServer("otp_enc_d", portNumber, handleClientEncryption);
}

#pragma clang diagnostic pop
