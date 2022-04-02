#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "syscall.h"
#include "exclude.hpp"

int
mutex_lock_app(mutex_t *mutex){
    auto [ret, err] = SyscallMutexLock(mutex);
    return ret;
}

int
mutex_unlock_app(mutex_t *mutex){
    auto [ret, err] = SyscallMutexUnlock(mutex);
    return ret;
}

void
var_set_app(int val){
    SyscallVarSet(val);
}