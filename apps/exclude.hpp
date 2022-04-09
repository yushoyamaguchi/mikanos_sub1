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


extern int
var_plus_one_app();

void
sleep_app(unsigned long ms);





#ifdef __cplusplus
} // extern "C"
#endif