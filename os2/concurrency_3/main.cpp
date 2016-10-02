/* References: http://timmurphy.org/2010/05/04/pthreads-in-c-a-minimal-working-example/ */
#include <pthread.h>
#include <stdio.h>

struct list_head {
    int data;
    struct list_head next;
};

struct list_head *list;

void *searcher() {
    return NULL;
}

void *inserter() {
    return NULL;
}

void *deleter() {
    return NULL;
}

int main() {

    pthread_t inc_x_thread;

    if (pthread_create(&inc_x_thread, NULL, inc_x)) {

        fprintf(stderr, "Error creating thread\n");
        return 1;

    }

    return 0;

}