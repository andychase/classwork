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
#include <dirent.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#define BUFFER_SIZE      1028

int portNumber = 8080;

const char *usage = "Usage: ftserver [port #]\n";
const char *badCommandMsg = "That command was not found\n";

int socketFd;

// Read/write pipe pair for communication with a socket
int pipes[2][2];
#define READ 0
#define WRITE 1
#define COMMAND_CONNECTION 0
#define DATA_CONNECTION 1

struct DataConnectionMessage {
    int client;
    int list;
    const char *fileToSend;
};

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


// ---- Vendor Functions ----
void readFromDir(const char *directory, char* buffer) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(directory)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            strcat(buffer, ent->d_name);
            strcat(buffer, "\n");
        }
        closedir(dir);
    } else {
        /* could not open directory */
    }
}


void *performDataConnection(void __unused *_) {
    struct DataConnectionMessage dataConnectionMessage;
    ssize_t sendSuccess;
    char *readFromConsoleSuccess;

    while (1) {
        /* --- Wait for, and recieve a client ---- */
        read(pipes[DATA_CONNECTION][READ], &dataConnectionMessage, sizeof(struct DataConnectionMessage));

        if (dataConnectionMessage.list) {
            writeConsoleTmpBuffer[0] = '\0';
            readFromDir(".", writeConsoleTmpBuffer);
            sendSuccess = send(dataConnectionMessage.client, writeConsoleTmpBuffer, strlen(writeConsoleTmpBuffer), 0);
        }

        /* --- Send --- */
//        sendSuccess = send(dataConnectionMessage.client, writeConsoleTmpBuffer, strlen(writeConsoleTmpBuffer), 0);
        writeConsoleBuffer[0] = '\0';
    }
}

void *performCommandConnection(void __unused *_) {
    int clientFd;
    ssize_t receiveSuccess;

    while (1) {
        /* --- Wait for, and recieve a client ---- */
        read(pipes[COMMAND_CONNECTION][READ], &clientFd, sizeof(int));

        receiveSuccess = 1;
        while (receiveSuccess != 0) {
            /* --- Receive --- */
            receiveSuccess = recv(clientFd, readSocketBuffer, BUFFER_SIZE, 0);
            if (receiveSuccess < BUFFER_SIZE)
                readSocketBuffer[receiveSuccess] = '\0';
            if (strstr(readSocketBuffer, "-l")) {
                struct DataConnectionMessage msg = {.client = clientFd, .list = 1, .fileToSend=NULL};
                write(pipes[DATA_CONNECTION][WRITE], &msg, sizeof(struct DataConnectionMessage));
            } else if (strstr(readSocketBuffer, "-g ")) {
                const char *fileToSend = malloc(strlen(readSocketBuffer) - 3 + 1);
                struct DataConnectionMessage msg = {.client = clientFd, .list = 0, .fileToSend=fileToSend};
                write(pipes[DATA_CONNECTION][WRITE], &msg, sizeof(struct DataConnectionMessage));
            } else {
                send(clientFd, badCommandMsg, strlen(badCommandMsg), 0);
            }
            /* --- Print --- */
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
    pipe(pipes[COMMAND_CONNECTION]);
    pipe(pipes[DATA_CONNECTION]);
    pthread_create(&threads[0], NULL, performCommandConnection, NULL);
    pthread_create(&threads[0], NULL, performDataConnection, NULL);

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
        /* --- Send client to handler thread --- */
        write(pipes[COMMAND_CONNECTION][WRITE], &clientFd, sizeof(int));
    }
}

#pragma clang diagnostic pop