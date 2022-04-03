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
    mutex_init_app(&mutex);
    mutex_lock_app(&mutex);
    var_set_app(5);
    sleep_app(4000);
    var=var_get_app();
    printf("var=%d\n",var);
    mutex_unlock_app(&mutex);
    return;
}