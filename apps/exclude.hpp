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
mutex_lock_app(mutex_t *mutex);

extern int
mutex_unlock_app(mutex_t *mutex);

void
var_set_app(int val);

#ifdef __cplusplus
} // extern "C"
#endif