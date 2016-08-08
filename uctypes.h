/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org>
*/
#ifndef __UCTYPES_H__
#define __UCTYPES_H__

// Include the two standard type headers
#include <stdbool.h>
#include <stdint.h>


////////////////////////////////////////////////////////////////////////////////
/** Useful pointer-to-function typedefs */

/** Pointer to function taking void, returning void */
typedef void (*PfTvRv)(void);

/** Pointer to function taking int, returning void */
typedef void (*PfTiRv)(int );

/** Pointer to function taking void, returning int */
typedef int  (*PfTvRi)(void);

/** Pointer to function taking pointer to void, returning void */
typedef void (*PfTvpRv)(void* );

/** Pointer to function taking pointer to void, returning pointer to void */
typedef void* (*PfTvpRvp)(void* );

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/** The standard "type macros" */

#ifndef NULL
/** Represents a null pointer */
#   define NULL  0
#endif
/** Represents a null pointer cast as void* */
#define NULLVP ((void*) 0)

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/** Macros and unions for for determining memory alignment */
/** Ok, there is no portable way to determine alignment for data types - this
 *  problem is machine- AND compiler-dependent. It boils down to the minimum
 *  alignment value equals sizeof(largest_data_type)/N, where N is 1, 2, 4...
 *  Since the alignment value can't be portably known, here is the hack:
 *  set it to the size of a pointer. This means 4 for Cortex M3 (it can access
 *  on byte boundaries, but 4 is the native wordsize and is pretty safe), and
 *  8 for 64-bit machines (i.e., pulse build servers).
 */
#define NATIVE_ALIGNMENT            sizeof(void*)
#define NATIVE_ALIGNMENT_MASK       (NATIVE_ALIGNMENT - 1)
#define ROUND_UP_NATIVE_ALIGNMENT(nbytes) \
 (Uint32 )((nbytes) & NATIVE_ALIGNMENT_MASK ? \
           (nbytes) + NATIVE_ALIGNMENT - ((nbytes) & NATIVE_ALIGNMENT_MASK) : (nbytes))

/** Here is a portable way to make sure that when we do allocations, we make
 *  sure we have rounded up to the size needed to hold multiples of the largest
 *  possible type. NOTE: not using long double's.
 */
union MaxDataTypeSize {
    int         i;
    long        l;
    long long   ll;
    void*       p;
    PfTvRv      fp;
    float       f;
    double      d;
};
#define MAX_DATATYPE_SIZE       sizeof(union MaxDataTypeSize)
#define MAX_DATATYPE_SIZE_MASK  (MAX_DATATYPE_SIZE - 1)
#define ROUND_UP_DATATYPE_SIZE(nbytes) \
 (Uint32 )((nbytes) & MAX_DATATYPE_SIZE_MASK ? \
           (nbytes) + MAX_DATATYPE_SIZE - ((nbytes) & MAX_DATATYPE_SIZE_MASK) : (nbytes))

/** Test that an address is properly aligned */
//#define IS_PTR_ALIGNED(addr)    (!(((intptr_t )addr) & (NATIVE_ALIGNMENT - 1)))

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/** Macros for converting between big- and little-endian
 *  Native host to network byte order short & long
 *  Network byte order to native host short & long
 */
#if defined(BIG_ENDIAN) && !defined(LITTLE_ENDIAN)
/** No conversion needed for big-endian to/from network byte order */
#   define htons(x)        (x)
#   define htonl(x)        (x)
#   define ntohs(x)        (x)
#   define ntohl(x)        (x)

#elif defined(LITTLE_ENDIAN) && !defined(BIG_ENDIAN)
/** Swap bytes appropriately for little-endian to/from network byte order */
#   define htons(x)        ((((Uint16)(x) & 0xFF00) >> 8) | \
                            (((Uint16)(x) & 0x00FF) << 8))
#   define htonl(x)        ((((Uint32)(x) & 0xFF000000) >> 24) | \
                            (((Uint32)(x) & 0x00FF0000) >>  8) | \
                            (((Uint32)(x) & 0x0000FF00) <<  8) | \
                            (((Uint32)(x) & 0x000000FF) << 24))
#   define ntohs           htons
#   define ntohl           htonl

#else
/** Replace with garbage that should fail compilation to ensure that either
 *  LITTLE_ENDIAN or BIG_ENDIAN (and not both) are defined
 */
#   define htons           @@@
#   define htonl           @@@@
#   define ntohs           @@@@@
#   define ntohl           @@@@@@
#endif

#endif  // __UCTYPES_H__

