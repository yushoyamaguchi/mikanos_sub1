#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>

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