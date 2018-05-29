/* CS 552 Fall 2006
 * Assignment 4
 * Submitted by : Avadh Patel
 * This file implements the Semaphore class 
 * that implements the semaphores and its functionality
 */

#ifndef RECUR_MUTEX_H
#define RECUR_MUTEX_H	

#include <pthread.h>

class RecursiveMutex {
  public:
    RecursiveMutex();
    ~RecursiveMutex();
    void lock();
    void unlock();
  private:
    int no_lock;
    pthread_mutex_t my_mutex;
    pthread_mutex_t condition_mutex;
    pthread_cond_t condition;
    pthread_t id_owner;
};

#endif
