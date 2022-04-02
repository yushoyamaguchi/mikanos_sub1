#include <cstdio>
#include <ctime>
#include <cctype>
#include <cerrno>
#include <sys/time.h>

#include "variable.hpp"
#include "../net/util.h"

static int variable=0;

int var_set(int val){
    variable=val;
    return 1;
}

int var_get(){
    infof("var=%d",variable);
    return variable;
}