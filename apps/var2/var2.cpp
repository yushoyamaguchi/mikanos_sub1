#include <unistd.h>
#include <sys/time.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "../syscall.h"
#include "../exclude.hpp"

#define BIG_IN_APP 500

extern "C" void main(){
    int var=0;
    int i=0;
    for(i=0;i<BIG_IN_APP;i++){
        var=var_plus_one_app();
        printf("var=%d\n",var);
    }
    return;
}