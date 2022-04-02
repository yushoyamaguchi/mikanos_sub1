

#include "../syscall.h"
#include "../exclude.hpp"

int main(){
    int var;
    mutex_t mutex;
    mutex_lock_app(&mutex);
    var_set_app(5);
    var=var_get_app();
    mutex_unlock_app(&mutex);
    return 0;
}