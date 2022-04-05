#include <unistd.h>
#include <sys/time.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "../syscall.h"
#include "../exclude.hpp"

extern "C" void main(){
    int var;
    mutex_t mutex;
    //mutex_t *smutex;
    mutex_init_app(&mutex);
    //smutex=get_sample_mutex_app();
    printf("mutex->locked=%d\n",mutex.locked);
    mutex_lock_app(&mutex);
    var_set_app(1);
    //sleep_app(6000);
    var=var_get_app();
    printf("var=%d\n",var);
    mutex_unlock_app(&mutex);
    return;
}