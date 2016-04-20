/*


REFERENCES:
* https://computing.llnl.gov/tutorials/pthreads/samples/hello.c
* http://mij.oltrelinux.com/devel/unixprg/
* https://stackoverflow.com/questions/1620918/cmake-and-libpthread
* http://www.tutorialspoint.com/cprogramming/c_structures.htm
* https://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
* https://stackoverflow.com/questions/4975340/int-to-unsigned-int-conversion

*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_random.h"

#define NUM_THREADS    2

struct WorkUnit {
    unsigned int unitNumber;
    unsigned int workTime;
};

int workPipe[2];

#define readPipe workPipe[0]
#define writePipe workPipe[1]

void *consumer(void *threadId) {
    struct WorkUnit work_message;
    long tid;
    ssize_t ret;
    tid = (long) threadId;

    for (; ;) {
        ret = read(readPipe, &work_message, sizeof(struct WorkUnit));
        if (ret == 0)
            break;
        sleep(work_message.workTime);
        printf("Thread #%ld consumed %u. Took %u seconds.\n", tid, work_message.unitNumber, work_message.workTime);

    };
    pthread_exit(NULL);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void producer() {
    struct WorkUnit producerMessage;
    unsigned int producerWaitTime;
    for (; ;) {
        producerMessage.unitNumber = get_random();
        producerMessage.workTime = get_random_between(2, 9);
        producerWaitTime = get_random_between(3, 7);
        write(writePipe, &producerMessage, sizeof(struct WorkUnit));
        sleep(producerWaitTime);
    }
}

#pragma clang diagnostic pop

int main(int argc, char *argv[]) {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    pipe(workPipe);

    for (t = 0; t < NUM_THREADS; t++) {
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, consumer, (void *) t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    producer();
    pthread_exit(NULL);
}
