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
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

/** @file
 * This file contains macros and functions that are generally useful for
 * instrumenting code with print functions.
 **/

/**
 *                      Debug Config Define Options
 * =====================================================================
 * The debug macros may be set in either of the following recommended methods:
 *   1) Compiler command-line options for the desired defines (e.g.,
 *      -DRUNTIME_PRINT_LEVEL).
 *   2) Inclusion of a config file (e.g., proj_config.h) with desire defines
 *      set. Note: the aforementioned config file MUST be #include'd before
 *      this file in the .c file.
 *   3) Explicitly setting the desired defines in a .c file. Note: the
 *      defines MUST come before this file in the .c file.
 *
 * Debug Print Macros
 * ----------------------------------------------
 * The following set of print macros are basically printf() functions that
 * are only enabled if DEBUG_PRINT is defined in the compile step and can be
 * turned on and off based on a configurable threshold. This threshold can be
 * set either through compile-time settings or at run-time via a global
 * variable. This configurable print verbosity functionality loosely mimics
 * the Linux syslog level-based logging.
 * The macros are named to match the print level as follows:
 *   PRINT     always prints regardless of level
 *   PRINTW    prints if level is WARNING or lower
 *   PRINTI    prints if level is INFO    or lower
 *   PRINTD    prints if level is DEBUG   or lower
 *   PRINTV    prints if level is ALL
 *
 * Additionally, the following set of print macros allow a print "scoping"
 * so that certain areas of code can be independently turned on or off. These
 * macros have the same verbosity control, but contain an additional first
 * parameter that controls the scoping of each invocation of printf(). These
 * macros are only available as when run-time print control is enabled.
 *   SPRINT     always prints regardless of level
 *   SPRINTW    prints if level is WARNING or lower
 *   SPRINTI    prints if level is INFO    or lower
 *   SPRINTD    prints if level is DEBUG   or lower
 *   SPRINTV    prints if level is ALL
 *
 * Debug Print Output Control
 * ----------------------------------------------
 * By defining the current print level to a particular threshold, print
 * output can be controlled between verbose and completely suppressed. To
 * control the print output, set the following:
 *   #define CURRENT_PRINT_LEVEL  <Print level setting below>
 *
 * Print level can be set to one of the following levels with the effect
 * specified:
 *   Print level setting           Effect
 *   .............................................................
 *     PRINT_LEVEL_NONE     All PRINTx() output suppressed
 *     PRINT_LEVEL_WARN     Only output from PRINTW()
 *     PRINT_LEVEL_INFO     Output from PRINTW() and PRINTI()
 *     PRINT_LEVEL_DEBUG    Output from PRINTW(), PRINTI(), and PRINTD()
 *     PRINT_LEVEL_ALL      All PRINTx() output enabled
 *
 * Run-time Print Output Control
 * ----------------------------------------------
 * As an alternative to fixed, compile-time print control, run-time control
 * is also possible with these macros. By setting and modifying a specific
 * global variable to one of the print levels listed above, print output
 * can be changed "on-the-fly". This is particularly useful when connected
 * to a debugger or when a terminal console is present that enables modifying
 * this variable. To enable run-time control, define the following:
 *   #define RUNTIME_PRINT_LEVEL
 *
 * In addition, the project must include two global variable as follows:
 *   unsigned short g_currentPrintLevel = <Print level setting above>;
 *   unsigned short g_currentPrintScope = <Print scope setting>;
 */

//////////////////////////////////////////////////////////////////////////////
#define PRINT_LEVEL_NONE     4
#define PRINT_LEVEL_WARN     3
#define PRINT_LEVEL_INFO     2
#define PRINT_LEVEL_DEBUG    1
#define PRINT_LEVEL_ALL      0

#define PRINT_SCOPE_NONE     0x0
#define PRINT_SCOPE_AREA00   (1 <<  0)
#define PRINT_SCOPE_AREA01   (1 <<  1)
#define PRINT_SCOPE_AREA02   (1 <<  2)
#define PRINT_SCOPE_AREA03   (1 <<  3)
#define PRINT_SCOPE_AREA04   (1 <<  4)
#define PRINT_SCOPE_AREA05   (1 <<  5)
#define PRINT_SCOPE_AREA06   (1 <<  6)
#define PRINT_SCOPE_AREA07   (1 <<  7)
#define PRINT_SCOPE_AREA08   (1 <<  8)
#define PRINT_SCOPE_AREA09   (1 <<  9)
#define PRINT_SCOPE_AREA10   (1 << 10)
#define PRINT_SCOPE_AREA11   (1 << 11)
#define PRINT_SCOPE_AREA12   (1 << 12)
#define PRINT_SCOPE_AREA13   (1 << 13)
#define PRINT_SCOPE_AREA14   (1 << 14)
#define PRINT_SCOPE_AREA15   (1 << 15)
#define PRINT_SCOPE_ALL      0xFFFF

extern unsigned short g_currentPrintLevel;
extern unsigned short g_currentPrintScope;

#ifdef DEBUG_PRINT
/** Define PRINTx macros (only creates output in debug builds)
 *  See above for details on using these macros.
 */
    extern int ucprintf(const char* fmt, ...);
#   define PRINT(fmt, args...)   ucprintf(fmt , ## args)

#   ifndef RUNTIME_PRINT_LEVEL
#       define PRINTW(fmt, args...)  \
            do { \
                if (CURRENT_PRINT_LEVEL <= PRINT_LEVEL_WARN) { ucprintf(fmt , ## args); } \
            } while (0)
#       define PRINTI(fmt, args...)  \
            do { \
                if (CURRENT_PRINT_LEVEL <= PRINT_LEVEL_INFO) { ucprintf(fmt , ## args); } \
            } while (0)
#       define PRINTD(fmt, args...)  \
            do { \
                if (CURRENT_PRINT_LEVEL <= PRINT_LEVEL_DEBUG) { ucprintf(fmt , ## args); } \
            } while (0)
#       define PRINTV(fmt, args...)  \
            do { \
                if (CURRENT_PRINT_LEVEL == PRINT_LEVEL_ALL) { ucprintf(fmt , ## args); } \
            } while (0)
#   else
#       define PRINTW(fmt, args...)  \
            do { \
                extern unsigned short g_currentPrintLevel; \
                if (g_currentPrintLevel <= PRINT_LEVEL_WARN) { ucprintf(fmt , ## args); } \
            } while (0)
#       define PRINTI(fmt, args...)  \
            do { \
                extern unsigned short g_currentPrintLevel; \
                if (g_currentPrintLevel <= PRINT_LEVEL_INFO) { ucprintf(fmt , ## args); } \
            } while (0)
#       define PRINTD(fmt, args...)  \
            do { \
                extern unsigned short g_currentPrintLevel; \
                if (g_currentPrintLevel <= PRINT_LEVEL_DEBUG) { ucprintf(fmt , ## args); } \
            } while (0)
#       define PRINTV(fmt, args...)  \
            do { \
                extern unsigned short g_currentPrintLevel; \
                if (g_currentPrintLevel == PRINT_LEVEL_ALL) { ucprintf(fmt , ## args); } \
            } while (0)

#       define SPRINT(scope, fmt, args...)  \
            do { \
                extern unsigned short g_currentPrintScope; \
                if (g_currentPrintScope & scope) { ucprintf(fmt , ## args); } \
            } while (0)
#       define SPRINTW(scope, fmt, args...)  \
            do { \
                extern unsigned short g_currentPrintLevel, g_currentPrintScope; \
                if ((scope & g_currentPrintScope) && (g_currentPrintLevel <= PRINT_LEVEL_WARN)) { ucprintf(fmt , ## args); } \
            } while (0)
#       define SPRINTI(scope, fmt, args...)  \
            do { \
                extern unsigned short g_currentPrintLevel, g_currentPrintScope; \
                if ((scope & g_currentPrintScope) && (g_currentPrintLevel <= PRINT_LEVEL_INFO)) { ucprintf(fmt , ## args); } \
            } while (0)
#       define SPRINTD(scope, fmt, args...)  \
            do { \
                extern unsigned short g_currentPrintLevel, g_currentPrintScope; \
                if ((scope & g_currentPrintScope) && (g_currentPrintLevel <= PRINT_LEVEL_DEBUG)) { ucprintf(fmt , ## args); } \
            } while (0)
#       define SPRINTV(scope, fmt, args...)  \
            do { \
                extern unsigned short g_currentPrintLevel, g_currentPrintScope; \
                if ((scope & g_currentPrintScope) && (g_currentPrintLevel <= PRINT_LEVEL_ALL)) { ucprintf(fmt , ## args); } \
            } while (0)
#   endif
#else
#   define PRINT(fmt, args...)
#   define PRINTW(fmt, args...)
#   define PRINTI(fmt, args...)
#   define PRINTD(fmt, args...)
#   define PRINTV(fmt, args...)

#   define SPRINT(scope, fmt, args...)
#   define SPRINTW(scope, fmt, args...)
#   define SPRINTI(scope, fmt, args...)
#   define SPRINTD(scope, fmt, args...)
#   define SPRINTV(scope, fmt, args...)
#endif


#endif  // __DEBUG_H__

