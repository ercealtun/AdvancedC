#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * hello_fun(){
    printf("hello world!\n");
    return NULL;
}

int main(int argc, char * argv[]){
    pthread_t thread = 0;
    pthread_create(&thread, NULL, hello_fun, NULL);

    // If we dont use sleep or the pthread_join functions main thread will finish before our self-structed thread.
    sleep(2);
    return 0;
}