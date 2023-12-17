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
    pthread_join(thread, NULL);
    return 0;
}