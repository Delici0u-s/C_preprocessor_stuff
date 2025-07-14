#ifndef D_MACROS_GET_ARG_H
#define D_MACROS_GET_ARG_H

#include <other/concat.h>
#include <list/RECCALL.h>
#include <common.h>

#define _GET_ARG_PART2_(a0, ...) a0
#define _GET_ARG_PART2(packet) _GET_ARG_PART2_ packet
#define _GET_ARG_PART_(a0, ...) (__VA_ARGS__)
#define _GET_ARG_PART(packet) _GET_ARG_PART_ packet
#define GET_ARG(pos, ...) _GET_ARG_PART2(RECCALL(pos, _GET_ARG_PART, (__VA_ARGS__)))

#endif
