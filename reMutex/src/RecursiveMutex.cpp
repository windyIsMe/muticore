/* CS 552 Fall 2006
 * Assignment 4
 * Submitted by : Avadh Patel
 * This file implements the Semaphore class 
 * that implements the semaphores and its functionality
 */

#include "RecursiveMutex.hpp"
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>

#define CHECK(x,s) \
		  if(x!=0) { \
		  	  perror(s); }

#define ECHECK(x,s) \
        if(x!=0) { perror(s); exit(-1); }

#define RCHECK(x,s) \
		  if(x!=0) { perror(s); return; }

RecursiveMutex::RecursiveMutex(){

  no_lock = 0;
  ECHECK(pthread_mutex_init(&my_mutex, NULL),"Can't initilize mutex");
  ECHECK(pthread_mutex_init(&condition_mutex, NULL),"Can't initilize condition");
  ECHECK(pthread_cond_init(&condition, NULL), "Can't initilize condition");
  id_owner = 0;
}

RecursiveMutex::~RecursiveMutex(){

  no_lock = 0;
  pthread_mutex_destroy(&my_mutex);
  CHECK(pthread_mutex_destroy(&condition_mutex),"Can't destroy mutex");
  CHECK(pthread_cond_destroy(&condition),"Can't destory condition");
}

void RecursiveMutex::lock(){
  
  CHECK(pthread_mutex_lock(&condition_mutex),"Error getting lock");
  if (pthread_equal(pthread_self(),id_owner)) {
    no_lock++;
    CHECK(pthread_mutex_unlock(&condition_mutex),"Error while unlocking");
    return;
  }
  while (no_lock > 0) {
    CHECK(pthread_cond_wait(&condition, &condition_mutex),"Error while cond_wait");
  }
  CHECK(pthread_mutex_lock(&my_mutex),"Error while lock");
  id_owner = pthread_self();
  no_lock++;
  CHECK(pthread_mutex_unlock(&condition_mutex),"Error while unlock");
  return;
}

void RecursiveMutex::unlock(){

  CHECK(pthread_mutex_lock(&condition_mutex),"Error while lock");
  if(pthread_equal(pthread_self(),id_owner)) {
    if(no_lock > 0) {
      no_lock--;
    }
    if(no_lock == 0){
      CHECK(pthread_cond_signal(&condition),"Error while signal");
      CHECK(pthread_mutex_unlock(&my_mutex),"Error while unlock");
    }
  }
  CHECK(pthread_mutex_unlock(&condition_mutex),"Error while unlock");
}

