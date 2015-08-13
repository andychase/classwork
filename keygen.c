#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CHARSET 26
#define STARTCHAR (int) 'A'

char randChar() {
    return (char) ((rand() % CHARSET) + STARTCHAR);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("USAGE: keygen keylength\n");
        return 1;
    } else {
        srand((unsigned int) time(NULL));

        int i;
        for (i = 0; i < atoi(argv[1]); i++)
            printf("%c", randChar());
    }
    printf("\n");
    return 0;
}
