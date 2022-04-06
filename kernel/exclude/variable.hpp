#include <cstdio>
#include <ctime>
#include <cctype>
#include <cerrno>
#include <sys/time.h>

#include "asmfunc.h"
#include "msr.hpp"
#include "logger.hpp"
#include "task.hpp"
#include "terminal.hpp"
#include "font.hpp"
#include "timer.hpp"
#include "keyboard.hpp"
#include "app_event.hpp"

#include "net/socket.h"
#include "../net/util.h"
#include "../net/port/mikanos.hpp"

#define BIG 10000

#define TIMER_ONESHOT_REL 1

extern int
var_set(int val);

extern int
var_get();

extern int 
var_plus_big();

extern int 
var_plus_one();