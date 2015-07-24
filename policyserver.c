/* Chasean / CS 372 / chatserv
 * References used:
 * - My Flash Policy Server: https://github.com/andychase/FlashPolicyServer
 * - Signal tutorial: http://www.yolinux.com/TUTORIALS/C++Signals.html
*/
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE      1028

int socketFd;
char buffer[MAX_BUFFER_SIZE];
const char *quitMsg = "\\quit";
size_t quitMsgSize = 6; // String size + \0
const char *usage = "Usage: chanserv [port #]";
int portNumber = 8080;

void signal_callback_handler(int signalNumber) {
    close(socketFd);
    exit(signalNumber);
}


int main(int argc, char *argv[]) {
    signal(SIGINT, signal_callback_handler);

    /* --- Read port from arguments or print usage -- */
    if (argc < 2 || atoi(argv[1]) == 0) {
        printf("%s", usage);
        return 1;
    } else {
        portNumber = atoi(argv[1]);
    }

    /* --- Create streaming socket --- */
    if ((socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket");
        return 1;
    }

    /* --- Initialize address/port structure --- */
    struct sockaddr_in self;
    self.sin_family = AF_INET;
    self.sin_port = htons(portNumber);
    self.sin_addr.s_addr = 0;
    self.sin_addr.s_addr = INADDR_ANY;
    self.sin_family = AF_INET;

    /* --- Assign a port number to the socket --- */
    if (bind(socketFd, (struct sockaddr *) &self, sizeof(self)) != 0) {
        perror("Error: socket bind");
        return 1;
    }

    /* --- Make it a listening socket --- */
    if (listen(socketFd, 20) != 0) {
        perror("socket--listen");
        return 1;
    }

    struct sockaddr_in client_address;
    socklen_t addressLength = sizeof(client_address);
    int clientFd;
    while (1) {
        /* --- Accept a client --- */
        clientFd = accept(socketFd, (struct sockaddr *) &client_address, &addressLength);

        /* --- Receive --- */
        recv(clientFd, buffer, MAX_BUFFER_SIZE, 0);

        /* --- Send --- */
        send(clientFd, quitMsg, quitMsgSize, 0);

        /* --- Close ---*/
        close(clientFd);
    }
}

