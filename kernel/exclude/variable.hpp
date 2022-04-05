#include <cstdio>
#include <ctime>
#include <cctype>
#include <cerrno>
#include <sys/time.h>

#include "../net/util.h"
#include "../net/port/mikanos.hpp"

#define BIG 1000000

extern int
var_set(int val);

extern int
var_get();

extern int 
var_plus_big();