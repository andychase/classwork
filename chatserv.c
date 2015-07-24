/* Chasean / CS 372 / chatserv
 * References used:
 * - My Flash Policy Server: https://github.com/andychase/FlashPolicyServer
 * - Signal tutorial: http://www.yolinux.com/TUTORIALS/C++Signals.html
*/
#include <sys/cdefs.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define BUFFER_SIZE      1028

int portNumber = 8080;
const char *quitMsg = "\\quit";

const char *usage = "Usage: chanserv [port #]";
const char *hostHandle = "SERV> ";

int socketFd;

// Read/write pipe pair for communication with a socket
int pipes[2][2];
#define READ 0
#define WRITE 1
#define SERVER_SEND 0
#define CLIENT_RECEIVE 1

void signal_callback_handler(int signalNumber) {
    printf("Caught signal %d, cleaning up\n", signalNumber);
    close(socketFd);
    exit(0);
}

void *writeConsoleToSocket(void __unused *_) {
    int clientFd;
    ssize_t sendSuccess;
    char *readFromConsoleSuccess;
    char inputBuffer[BUFFER_SIZE];

    while (1) {
        /* --- Wait for, and recieve a client ---- */
        read(pipes[SERVER_SEND][READ], &clientFd, sizeof(int));

        sendSuccess = 1;
        while (sendSuccess > 0 && !strstr(inputBuffer, quitMsg)) {
            /* --- Print prompt --- */
            printf("%s", hostHandle);
            /* --- Read message from standard input --- */
            readFromConsoleSuccess = fgets(inputBuffer, BUFFER_SIZE, stdin);
            if (!readFromConsoleSuccess)
                break;
            /* --- Send --- */
            sendSuccess = send(clientFd, hostHandle, strlen(hostHandle), 0);
            if (!sendSuccess)
                break;
            sendSuccess = send(clientFd, inputBuffer, strlen(inputBuffer), 0);
        }
        // If user wrote the quit message, close socket
        if (strstr(inputBuffer, quitMsg))
            close(clientFd);
        inputBuffer[0] = '\0';
    }
}

void *readSocketToConsole(void __unused *_) {
    int clientFd;
    ssize_t receiveSuccess;
    char inputBuffer[BUFFER_SIZE];

    while (1) {
        /* --- Wait for, and recieve a client ---- */
        read(pipes[CLIENT_RECEIVE][READ], &clientFd, sizeof(int));

        receiveSuccess = 1;
        while (receiveSuccess != 0) {
            /* --- Receive --- */
            receiveSuccess = recv(clientFd, inputBuffer, BUFFER_SIZE, 0);
            /* --- Print --- */
            printf("\n%s%s", inputBuffer, hostHandle);
            fflush(stdout);
        }
        inputBuffer[0] = '\0';
        printf("\n%s\n", "Client disconnected");
    }
}

int main(int argc, char *argv[]) {
    signal(SIGINT, signal_callback_handler);

    /* --- Set up client handler threads ---*/
    pthread_t threads[2];
    // Create pipes for sending clients
    pipe(pipes[CLIENT_RECEIVE]);
    pipe(pipes[SERVER_SEND]);
    pthread_create(&threads[0], NULL, writeConsoleToSocket, NULL);
    pthread_create(&threads[0], NULL, readSocketToConsole, NULL);

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
    printf("Starting chatserv on port %d\n", portNumber);

    struct sockaddr_in client_address;
    socklen_t addressLength = sizeof(client_address);
    int clientFd;
    while (1) {
        /* --- Accept a client --- */
        clientFd = accept(socketFd, (struct sockaddr *) &client_address, &addressLength);
        printf("%s\n", "Client connected");
        /* --- Send client to handler threads --- */
        write(pipes[CLIENT_RECEIVE][WRITE], &clientFd, sizeof(int));
        write(pipes[SERVER_SEND][WRITE], &clientFd, sizeof(int));
    }
}
