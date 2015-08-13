//
// Created by Andy Chase on 8/12/15.
//

#ifndef PROJECT4_HEADER_FILE_H
#define PROJECT4_HEADER_FILE_H
int startServer(char *serverName, int portNumber, void *(*callback)(void *));
void handleClient(int clientFd, int encryptionMode, char *buffer, int *resultBuffer, int *keyBuffer, int *msgBuffer);
#endif //PROJECT4_HEADER_FILE_H
