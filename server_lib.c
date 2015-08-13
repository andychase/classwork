/* Shared Server Framework
 * References used:
 * - My Flash Policy Server: https://github.com/andychase/FlashPolicyServer
 * - Signal tutorial: http://www.yolinux.com/TUTORIALS/C++Signals.html
*/
#include "cipher_lib.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

int socketFd;

void signal_callback_handler(int signalNumber) {
    printf("Caught signal %d, cleaning up\n", signalNumber);
    close(socketFd);
    exit(0);
}

// --- Socket Utils --- //

void pullFromSocket(int socket, char *buffer, size_t length) {
    ssize_t bytesReceived;
    size_t receivedLength = 0;
    while (receivedLength < length) {
        bytesReceived = recv(socket, buffer + receivedLength, length - receivedLength, 0);
        if (bytesReceived <= 0)
            break;
        else
            receivedLength += bytesReceived;
    }
}

void pushToSocket(int socket, char *buffer, size_t length) {
    ssize_t bytesSent;
    size_t sentLength = 0;
    while (sentLength < length) {
        bytesSent = send(socket, buffer + sentLength, length - sentLength, 0);
        if (bytesSent <= 0)
            break;
        else
            sentLength += bytesSent;
    }
}

// --- Client Functions --- //

int openConnectSocket(int port) {
    int socket_desc;
    struct sockaddr_in server;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }

    server.sin_addr.s_addr = 0;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (connect(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {
        puts("connect error\n");
        return -1;
    } else {
        return socket_desc;
    }
}

void handleServerConnection(int clientFd, int encryptionMode,
                            char *keyBuffer, char *msgBuffer, char *resultBuffer, size_t size) {
    char sizeBuf[] = {(char) size, (char) (size_t) encryptionMode};
    pushToSocket(clientFd, sizeBuf, sizeof(char) * 2);
    pushToSocket(clientFd, keyBuffer, size);
    pushToSocket(clientFd, msgBuffer, size);
    pullFromSocket(clientFd, resultBuffer, size);
}

// ---- Server Functions ---- //

int startServer(char *serverName, int portNumber, void (*callback)(int)) {
    signal(SIGINT, signal_callback_handler);

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
    printf("Starting %s on port %d\n", serverName, portNumber);

    struct sockaddr_in client_address;
    socklen_t addressLength = sizeof(client_address);
    int clientFd;
    while (1) {
        /* --- Accept a client --- */
        clientFd = accept(socketFd, (struct sockaddr *) &client_address, &addressLength);
        printf("%s\n", "Client connected");
        /* --- Process connection in child process --- */
        int pid = fork();
        if (pid == 0) {
            callback(clientFd);
            return 0;
        } else if (pid == -1) {
            return 1;
        }
    }
}

void handleClient(int clientFd, int encryptionMode, char *buffer, int *resultBuffer, int *keyBuffer, int *msgBuffer) {
    ssize_t receiveLength;
    ssize_t sendSuccess;
    size_t msgAndKeyLength;
    size_t isEncrypting;

    while (1) {
        // Read the key/msg length and the is_encrypting boolean
        receiveLength = recv(clientFd, buffer, sizeof(char) * 2, 0);
        if (!receiveLength)
            return;

        msgAndKeyLength = (size_t) buffer[0];
        isEncrypting = (size_t) buffer[1];
        if (isEncrypting != encryptionMode) {
            close(clientFd);
            return;
        }


        pullFromSocket(clientFd, buffer, msgAndKeyLength);
        buffer[msgAndKeyLength] = '\0';
        otp_encode(keyBuffer, buffer);

        pullFromSocket(clientFd, buffer, msgAndKeyLength);
        buffer[msgAndKeyLength] = '\0';
        otp_encode(msgBuffer, buffer);
        if (encryptionMode)
            otp_encrypt(resultBuffer, msgBuffer, keyBuffer, (int) msgAndKeyLength);
        else
            otp_decrypt(resultBuffer, msgBuffer, keyBuffer, (int) msgAndKeyLength);

        otp_decode(buffer, resultBuffer, (int) msgAndKeyLength);
        sendSuccess = send(clientFd, buffer, msgAndKeyLength, 0);
        if (!sendSuccess)
            return;
    }
}

#pragma clang diagnostic pop
