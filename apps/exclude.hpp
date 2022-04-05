#ifdef __cplusplus
#include <cstddef>
#include <cstdint>

extern "C" {
#else
#include <stddef.h>
#include <stdint.h>
#endif

#include "../kernel/net/port/mikanos.hpp"

extern int
mutex_init_app(mutex_t *mutex);

extern int
mutex_lock_app(mutex_t *mutex);

extern int
mutex_unlock_app(mutex_t *mutex);

void
var_set_app(int val);

extern int
var_get_app();

extern int
var_plus_one_app();

void
sleep_app(unsigned long ms);

mutex_t* 
get_sample_mutex_app();



#ifdef __cplusplus
} // extern "C"
#endif