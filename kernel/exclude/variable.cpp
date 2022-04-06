#include <cstdio>
#include <ctime>
#include <cctype>
#include <cerrno>
#include <sys/time.h>

#include "variable.hpp"
#include "../net/util.h"
#include "../net/port/mikanos.hpp"




static int variable=0;

static mutex_t mutex=MUTEX_INITIALIZER;

int var_set(int val){
    variable+=val;
    return 1;
}

int var_get(){
    infof("var=%d",variable);
    return variable;
}


int var_plus_big(){
    int i=0;
    for(i=0;i<BIG;i++){
        mutex_lock(&mutex);
        variable+=1;
        mutex_unlock(&mutex);
    }
    return variable;
}


int isPrimeNumber(long n) {

    long i;

    if (n < 2) {
        /* 2未満の場合は素数でない */
        return 0;
    }

    /* nが2〜n-1で割り切れるかどうかを確認 */
    for (i = 2; i < n; i++) {
        if (n % i == 0) {
            /* 2〜n-1で割り切れる場合はnは素数でない */
            return 0;
        }
    }

    return 1;
}


int var_plus_one(){
    int buf=0;
    mutex_lock(&mutex);
    buf=variable;
    long p=0;
    int arr[BIG];
    while(p<=BIG){
        if(isPrimeNumber(p)){
            arr[p]=1;
        }
        p++;
    }
    variable=buf+1;
    mutex_unlock(&mutex);
    const auto time=timer_manager->CurrentTick();
    infof("%d",arr[time]);
    return variable;
}