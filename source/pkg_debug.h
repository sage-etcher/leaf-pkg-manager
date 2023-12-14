/* run once */
#pragma once
#ifndef __PKG_DEBUG_HEADER__
#define __PKG_DEBUG_HEADER__

#include <stdio.h>
#include <malloc.h>


/* enable/disable debug mode */
#undef DEBUG_MODE
#undef DEBUG_INFO_STDOUT
#define DEBUG_INFO_LOGFILE

extern const char *debug_log_file;

#ifdef DEBUG_MODE
/* make sure that function return types are handled */
#define UNUSED_RESULT __attribute__((unused-result))
/* log dynamic allocations and frees (to better find memory leaks */
#define TRACE_MALLOC(s) (debug_log_malloc (s, __LINE__, __FILE__))
#define TRACE_CALLOC(t,s) (debug_log_calloc (t, s, __LINE__, __FILE__))
#define TRACE_REALLOC(p,s) (debug_log_realloc (p, s, __LINE__, __FILE__))
#define TRACE_FREE(p) (debug_log_free (p, __LINE__, __FILE__))

#endif /* def DEBUG_MODE */

#ifndef DEBUG_MODE
/* default do nothing expansions */
#define UNUSED_RESULT

#define TRACE_MALLOC(s) (malloc (s))
#define TRACE_CALLOC(t,s) (calloc (t, s))
#define TRACE_REALLOC(p,s) (realloc (p, s))
#define TRACE_FREE(p) (free (p))
#endif /* ndef DEBUG_MODE */



/* debug logging functions */
void *debug_log_malloc (size_t size, const int line, const char *file);
void *debug_log_calloc (size_t size, size_t num, const int line, const char *file);
void *debug_log_realloc (void *ptr, size_t size, const int line, const char *file);
void debug_log_free (void *ptr, const int line, const char *file);


#endif /* run once */

