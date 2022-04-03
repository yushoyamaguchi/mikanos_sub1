#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "syscall.h"
#include "exclude.hpp"

int
mutex_init_app(mutex_t *mutex){
    auto [ret, err] = SyscallMutexInit(mutex);
    return ret;
}

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

int
var_get_app(){
    auto [ret, err] =SyscallVarGet();
    return ret;
}

void
sleep_app(unsigned long ms){
    const unsigned long duration_ms = (const unsigned long)ms;
    const auto timeout = SyscallCreateTimer(TIMER_ONESHOT_REL, 1, duration_ms);
    AppEvent events[1];
    while (true) {
        SyscallReadEvent(events, 1);
        if (events[0].type == AppEvent::kTimerTimeout) {
            //printf("%lu msecs elapsed!\n", duration_ms);
            break;
        } else {
            //printf("unknown event: type = %d\n", events[0].type);
        }
    }
    return;
}

