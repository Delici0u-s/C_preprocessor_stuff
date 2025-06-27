/* Auto-generated HAS_N_ARGS header */
#ifndef HAS_N_ARGS_H
#define HAS_N_ARGS_H

#include "var_count.h"
#include "num_cmp.h"

#define HAS_N_ARGS(N, ...) SAME_NUM(N, VAR_COUNT(__VA_ARGS__))

#endif /* HAS_N_ARGS_H */