/* Chasean / CS 372 / ftserver
 * References used:
 * - My Flash Policy Server: https://github.com/andychase/FlashPolicyServer
 * - Signal tutorial: http://www.yolinux.com/TUTORIALS/C++Signals.html
 * - The previous chat client/server project
*/
#include <sys/cdefs.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#define BUFFER_SIZE      1028

int portNumber = 8080;
const char *quitMsg = "\\quit";

const char *usage = "Usage: ftserver [port #]\n";
const char *hostHandle = "SERV> ";

int socketFd;

// Read/write pipe pair for communication with a socket
int pipes[2][2];
#define READ 0
#define WRITE 1
#define SERVER_SEND 0
#define CLIENT_RECEIVE 1

// For writeConsoleToSocket only (initialized here to save stack space)
char writeConsoleBuffer[BUFFER_SIZE];
char writeConsoleTmpBuffer[BUFFER_SIZE];

// For readSocketToConsole only
char readSocketBuffer[BUFFER_SIZE];

void signal_callback_handler(int signalNumber) {
    printf("Caught signal %d, cleaning up\n", signalNumber);
    close(socketFd);
    exit(0);
}

void *writeConsoleToSocket(void __unused *_) {
    int clientFd;
    ssize_t sendSuccess;
    char *readFromConsoleSuccess;

    while (1) {
        /* --- Wait for, and recieve a client ---- */
        read(pipes[SERVER_SEND][READ], &clientFd, sizeof(int));

        sendSuccess = 1;
        while (sendSuccess > 0 && !strstr(writeConsoleBuffer, quitMsg)) {
            /* --- Print prompt --- */
            printf("%s", hostHandle);
            fflush(stdout);
            /* --- Read message from standard input --- */
            readFromConsoleSuccess = fgets(writeConsoleBuffer, BUFFER_SIZE, stdin);
            if (!readFromConsoleSuccess)
                break;
            /* --- Add handle to message --- */
            strcpy(writeConsoleTmpBuffer, hostHandle);
            strcat(writeConsoleTmpBuffer, writeConsoleBuffer);

            /* --- Send --- */
            sendSuccess = send(clientFd, writeConsoleTmpBuffer, strlen(writeConsoleTmpBuffer), 0);
        }
        // If user wrote the quit message, close socket
        if (strstr(writeConsoleBuffer, quitMsg))
            close(clientFd);
        writeConsoleBuffer[0] = '\0';
    }
}

void *readSocketToConsole(void __unused *_) {
    int clientFd;
    ssize_t receiveSuccess;

    while (1) {
        /* --- Wait for, and recieve a client ---- */
        read(pipes[CLIENT_RECEIVE][READ], &clientFd, sizeof(int));

        receiveSuccess = 1;
        while (receiveSuccess != 0) {
            /* --- Receive --- */
            receiveSuccess = recv(clientFd, readSocketBuffer, BUFFER_SIZE, 0);
            if (receiveSuccess < BUFFER_SIZE)
                readSocketBuffer[receiveSuccess] = '\0';
            /* --- Print --- */
            printf("\n%s%s", readSocketBuffer, hostHandle);
            fflush(stdout);
        }
        readSocketBuffer[0] = '\0';
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
    printf("Starting ftserver on port %d\n", portNumber);

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

#pragma clang diagnostic pop