#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <malloc.h>

pthread_t thread_pool[50];

struct thread_0_request {
    int status;
    char hi[50];
};

struct thread_0_response {
    int status;
    char hi[50];
};

void* thread_0(void *callers){
    struct thread_0_request  *req;
    req = (struct thread_0_request*)callers;


    printf("thread_0_req->hi = %s, status=%d\n",req->hi,req->status);
    printf("called thread 0\n");
    struct thread_0_response *resp_instance;
    resp_instance = malloc(sizeof(struct thread_0_response));
    strcpy(resp_instance->hi,"hi");
    resp_instance->status = req->status + 1;

    
    return (void*)resp_instance;
}

void* thread_1(void* callers){
    printf("called thread 0\n");
    return NULL;
}

// an api server which handle get/set request
int main() {
    struct thread_0_request req;
    strcpy(req.hi,"hello");
    req.status = 2;

    pthread_create(&thread_pool[0],NULL,thread_0,&req);
    printf("pthread[0]:%llu\n",thread_pool[0]);
    struct thread_0_response *rsp;
    pthread_join(thread_pool[0],(void**)&rsp);
    
    
    // panic here
    printf("returned status=%d\n",rsp->status);
    pthread_create(&thread_pool[1],NULL,thread_1,NULL);
}