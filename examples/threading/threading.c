#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
//#define DEBUG_LOG(msg,)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
//#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

#define DEBUG_LOG(msg,...) printf(msg, ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    thread_func_args->thread_complete_success = false;
    
    usleep(1000*(thread_func_args->wait_to_obtain_ms));
    DEBUG_LOG("****Waiting to OBTAIN Mutex****\n");

    if(pthread_mutex_lock(thread_func_args->mutex) != 0){
	    ERROR_LOG("****Mutex Not Locked****\n");
	    DEBUG_LOG("****Mutex Not Locked****\n");
	    return thread_func_args;

    }

    usleep(1000*(thread_func_args->wait_to_release_ms));
    DEBUG_LOG("****Waiting to RELEASE Mutex****\n");

    if (pthread_mutex_unlock(thread_func_args->mutex) != 0) {
        DEBUG_LOG("****Mutex Locked****\n");
        ERROR_LOG("****Mutex Locked****\n");
        return thread_func_args;
    }
    thread_func_args->thread_complete_success = true;
    
    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
    struct thread_data *local_data;
    thread_data_local = malloc(sizeof(struct thread_data));

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, 2400);

    local_data->thread = thread;
    local_data->mutex = mutex;
    local_data->wait_to_obtain_ms = wait_to_obtain_ms;
    local_data->wait_to_release_ms = wait_to_release_ms;

    int thread_status = pthread_create(thread, &attr, threadfunc, (void*)local_data);

    if (thread_status) {
        DEBUG_LOG("****Thread not created****\n");
        return false;
    }
    else {
        DEBUG_LOG("****Thread created successfully!****\n");
        return true;
    }
}

