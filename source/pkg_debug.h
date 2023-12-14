/* run once */
#pragma once
#ifndef __PKG_DEBUG_HEADER__
#define __PKG_DEBUG_HEADER__

#include <stdio.h>
#include <malloc.h>

/* make sure that function return types are handled */
#define WARN_UNUSED_RESULT __attribute__((warn_unused_result))


/* enable/disable debug mode */
#undef DEBUG_MODE

/* use basic fucntions if not in debug mode */
#ifndef DEBUG_MODE
#define TRACE_MALLOC(size)       (malloc  (size))
#define TRACE_CALLOC(size,count) (calloc  (size, count))
#define TRACE_REALLOC(ptr,size)  (realloc (ptr,  size))
#define TRACE_FREE(ptr)          (free    (ptr))
#define TRACE_FOPEN(name,access) (fopen   (name, access))
#define TRACE_FCLOSE(file)       (fclose  (file))

#endif /* ndef DEBUG_MODE */


/* use custom functions if in debug mode */
#ifdef DEBUG_MODE

/* where to log information to */
#undef DEBUG_LOG_TO_STDOUT
#undef DEBUG_LOG_TO_LOGFILE

extern const char *debug_log_file;

/* log dynamic allocations and frees (to better find memory leaks */
#define TRACE_MALLOC(size)       (debug_malloc  (size,         __LINE__, __FILE__))
#define TRACE_CALLOC(size,count) (debug_calloc  (size, count,  __LINE__, __FILE__))
#define TRACE_REALLOC(ptr,size)  (debug_realloc (ptr,  size,   __LINE__, __FILE__))
#define TRACE_FREE(ptr)          (debug_free    (ptr,          __LINE__, __FILE__))
#define TRACE_FOPEN(name,access) (debug_fopen   (name, access, __LINE__, __FILE__))
#define TRACE_FCLOSE(file)       (debug_fclose  (file,         __LINE__, __FILE__))


/* debug logging functions */
void *debug_malloc  (size_t bytes, const int line_number, const char *source_file);
void *debug_calloc  (size_t bytes, size_t count, const int line_number, const char *source_file);
void *debug_realloc (void *ptr, size_t bytes, const int line_number, const char *source_file);
void  debug_free    (void *ptr, const int line_number, const char *source_file);
FILE *debug_fopen   (const char *filename, const char *access_specifier, const int line_number, const char *source_file);
int   debug_fclose  (FILE *fp, const int line_number, const char *source_file);


#endif /* def DEBUG_MOD */

#endif /* run once */


/* end of file */
