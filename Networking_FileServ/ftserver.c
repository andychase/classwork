/* Chasean / CS 372 / ftserver
 * References used:
 * - My Flash Policy Server: https://github.com/andychase/FlashPolicyServer
 * - Signal tutorial: http://www.yolinux.com/TUTORIALS/C++Signals.html
 * - The previous chat client/server project
 * - http://www.binarytides.com/socket-programming-c-linux-tutorial/
*/
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/fcntl.h>
#include <sys/errno.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#define BUFFER_SIZE      1028

int portNumber = 8080;

const char *usage = "Usage: ftserver [port #]\n";
const char *badCommandMsg = "That command was not found\n";
const char *badFileMsg = "That file was not found or an error occured while opening it\n";

int socketFd;

// Read/write pipe pair for communication with a socket
int pipes[2][2];
#define READ 0
#define WRITE 1
#define COMMAND_CONNECTION 0
#define DATA_CONNECTION 1

struct DataConnectionMessage {
    int client;
    struct in_addr address;
    int port;
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
void readFromDir(char *buffer) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(".")) != NULL) {
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

// --- End Vendor functions ---

void copyFile(int from, int to) {
    size_t bytesRead;
    char *buf[BUFSIZ];
    while (1) {
        bytesRead = (size_t) read(from, buf, sizeof(buf));
        if (!bytesRead)
            return;
        write(to, buf, bytesRead);
    }
}

int openListenSocket(struct DataConnectionMessage req) {
    int socket_desc;
    struct sockaddr_in server;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = req.address.s_addr;
    server.sin_family = AF_INET;
    server.sin_port = htons(req.port);

    if (connect(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {
        puts("connect error\n");
        return -1;
    } else {
        return socket_desc;
    }
}


void *performDataConnection(void *_) {
    struct DataConnectionMessage dataConnectionMessage;

    while (1) {
        /* --- Wait for, and recieve a client ---- */
        read(pipes[DATA_CONNECTION][READ], &dataConnectionMessage, sizeof(struct DataConnectionMessage));

        /* --- If -l sent, send dir listing --- */
        if (dataConnectionMessage.list) {
            writeConsoleTmpBuffer[0] = '\0';
            readFromDir(writeConsoleTmpBuffer);
            int socket = openListenSocket(dataConnectionMessage);
            send(socket, writeConsoleTmpBuffer, strlen(writeConsoleTmpBuffer), 0);
            close(socket);
        } else {
            /* --- Otherwise check file --- */
            const char *fileToSend = dataConnectionMessage.fileToSend + 3;
            int fileFd = open(fileToSend, O_RDONLY);
            free((void *) dataConnectionMessage.fileToSend);
            if (fileFd != -1) {
                int socket = openListenSocket(dataConnectionMessage);
                copyFile(fileFd, socket);
                close(socket);
                if (errno) {
                    strcat(writeConsoleBuffer, strerror(errno));
                    strcat(writeConsoleBuffer, "\n");
                }
                send(dataConnectionMessage.client, writeConsoleBuffer, strlen(writeConsoleBuffer), 0);
            } else {
                strcat(writeConsoleBuffer, badFileMsg);
                strcat(writeConsoleBuffer, "\n");
                strcat(writeConsoleBuffer, strerror(errno));
                strcat(writeConsoleBuffer, "\n");
                send(dataConnectionMessage.client, writeConsoleBuffer, strlen(writeConsoleBuffer), 0);
            }
        }
        writeConsoleBuffer[0] = '\0';
    }
}

void *performCommandConnection(void *_) {
    struct DataConnectionMessage requestMessage;
    int clientFd;
    int clientPort;
    ssize_t receiveSuccess;

    while (1) {
        /* --- Wait for, and recieve a client ---- */
        read(pipes[COMMAND_CONNECTION][READ], &requestMessage, sizeof(struct DataConnectionMessage));
        clientFd = requestMessage.client;

        clientPort = 0;
        receiveSuccess = 1;
        while (receiveSuccess != 0) {
            /* --- Receive --- */
            receiveSuccess = recv(clientFd, readSocketBuffer, BUFFER_SIZE, 0);
            // Remove newline
            if (readSocketBuffer[strlen(readSocketBuffer) - 1] == '\n')
                readSocketBuffer[strlen(readSocketBuffer) - 1] = '\0';
            // If partial response received, terminate any extra
            if (receiveSuccess < BUFFER_SIZE)
                readSocketBuffer[receiveSuccess] = '\0';

            // Sort Commands
            if (clientPort < 1) {
                // First response should be the data port
                clientPort = atoi(readSocketBuffer);
            } else if (strstr(readSocketBuffer, "-l")) {
                // List
                struct DataConnectionMessage msg = {
                    .client = clientFd, .address = requestMessage.address, .port = clientPort, .list = 1};
                write(pipes[DATA_CONNECTION][WRITE], &msg, sizeof(struct DataConnectionMessage));
                close(clientFd);
                break;
            } else if (strstr(readSocketBuffer, "-g ")) {
                // Send file
                const char *fileToSend = strdup(readSocketBuffer);
                struct DataConnectionMessage msg = {
                    .client = clientFd, .address = requestMessage.address, .port = clientPort, .fileToSend=fileToSend};
                write(pipes[DATA_CONNECTION][WRITE], &msg, sizeof(struct DataConnectionMessage));
                close(clientFd);
                break;
            } else {
                // Return bad message
                send(clientFd, badCommandMsg, strlen(badCommandMsg), 0);
                close(clientFd);
                break;
            }
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
        struct DataConnectionMessage msg = {
            .client = clientFd,
            .address = client_address.sin_addr
        };
        write(pipes[COMMAND_CONNECTION][WRITE], &msg, sizeof(struct DataConnectionMessage));
    }
}

#pragma clang diagnostic pop
