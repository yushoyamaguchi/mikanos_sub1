#include <cstdio>
#include <ctime>
#include <cctype>
#include <cerrno>
#include <sys/time.h>

#include "variable.hpp"
#include "../net/util.h"
#include "../net/port/mikanos.hpp"


static int variable=0;

static mutex_t mutex={0};

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

int var_plus_one(){
    variable+=1;
    return variable;
}