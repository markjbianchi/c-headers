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
#ifndef __MACROS_H__
#define __MACROS_H__

/** @file
 * This file contains common defines and macros that are generally useful for
 * all application code.
 **/

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/** If mixing C in C++ files, these macros help with protecting C from name-mangling */
#ifdef __cplusplus
/** Begins a C region when included in a C++ file */
#   define EXTERN_CPP_START extern "C" {
/** Ends a C region in C++ files */
#   define EXTERN_CPP_END }
#else
#   define EXTERN_CPP_START
#   define EXTERN_CPP_END
#endif

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/** Define a loop that has no exit case */
#ifndef FOREVER
#   define FOREVER     for ( ; ; )
#endif

/** Macro to calculate an array dimension */
#ifndef NUM_ARRAY_ELEM
#   define NUM_ARRAY_ELEM(array)   (sizeof(array) / sizeof((array)[0]))
#endif

/** Operators for linked list structures */
/** assumes link pointers in structure are named "next" and "prev" */
#ifndef NEXT
#   define NEXT(x)  ((x)->next)
#endif
#ifndef PREV
#   define PREV(x)  ((x)->prev)
#endif

/** Test for even or odd value */
#ifndef IS_ODD
#   define IS_ODD(val)     ((val) & 0x1)
#endif
#ifndef IS_EVEN
#   define IS_EVEN(val)    (!((val) & 0x1))
#endif

/** Typical math min, max, abs, etc functions performed as macros */
/** Note that these arguments are evaluated more than once, so if they have
 *  any prefix/postfix operators, you may get unexpected results, e.g.,
 *  int result = CLIP(*pData++, 0, 255);
 *  ALIGNB(), FLOORB(), and CEILB() are faster versions if only aligning
 *  to power of 2 numbers.
 */
#ifndef ALIGNB
#   define ALIGNB(val, align)  (((val) + ((align) - 1)) & ~((align) - 1))
#endif
#ifndef ALIGN
#   define ALIGN(val, align)   ((((val) + ((align) - 1)) / (align)) * (align))
#endif
#ifndef FLOORB
#   define FLOORB(val, align)  ((val) & ~((align) - 1))
#endif
#ifndef FLOOR
#   define FLOOR(val, align)   (((val) / (align)) * (align))
#endif
#ifndef CEILB
#   define CEILB(val, align)   ALIGNB(val, align)
#endif
#ifndef CEIL
#   define CEIL(val, align)    ALIGN(val, align)
#endif
#ifndef CLIP
#   define CLIP(val, min, max) (((val) < (min)) ? (min) : (((val) > (max)) ? (max) : (val)))
#endif
#ifndef UCLIP
#   define UCLIP(val, max)     (((val) > (max)) ? (max) : (val))
#endif
#ifndef LCLIP
#   define LCLIP(val, min)     (((val) < (min)) ? (min) : (val))
#endif
#ifndef MIN
#   define MIN(x, y)           (((x) < (y)) ?  (x) : (y))
#endif
#ifndef MAX
#   define MAX(x, y)           (((x) > (y)) ?  (x) : (y))
#endif
#ifndef ABS
#   define ABS(x)              (((x) <  0) ? -(x) : (x))
#endif

/** Typical bit operations as macros */
/** Shifts to the right if shift if positive and to the left if shift is negative
 *  Same caveat applies regarding multiple evaluations.
 */
#ifndef BITSHIFT
#   define BITSHIFT(val, shift) (((shift) >= 0) ? ((val) >> (shift)) : ((val) << -(shift)))
#endif

/** Sets the n-th bit of x to 1 */
#ifndef BITSET
#   define BITSET(x, n)        ((x) | (1 << (n)))
#endif

/** Clears the n-th bit of x to 0 */
#ifndef BITCLR
#   define BITCLR(x, n)        ((x) & (~(1 << (n))))
#endif

/** returns the n-th bit of x */
#ifndef BITGET
#   define BITGET(x, n)        (((x) >> (n)) & 0x1)
#endif


/** @def FCC
 * Creates a uint32_ from a four character code "code".
 * Used for making enum values readable in memory.
 */
#ifndef FCC
#    define FCC(ch1, ch2, ch3, ch4) (((uint32_t)(ch4) << 24) | \
                                     ((uint32_t)(ch3) << 16) | \
                                     ((uint32_t)(ch2) <<  8) | \
                                     ((uint32_t)(ch1) <<  0) )
#endif

/** Makes strcmp more readable, i.e., STRCMP("123", ==, numVar) */
#define STRCMP(a,R,b)       (strcmp(a,b) R 0)

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/** the FILENAME macro extracts just the name of the file from the full path __FILE__ */
#ifndef FILENAME
#   define FILENAME         (const char* )(strrchr(__FILE__, '/') + 1)
#endif

#endif  // __MACROS_H__

