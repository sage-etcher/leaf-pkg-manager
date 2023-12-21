/* 
 * This source file is a part of the Leaf Package Manager.
 *
 * /source/debug.h
 * Contains important debugging macros and prototypes for '/source/debug.c'.
 *
 */

/* 
 * Copyright 2023 Sage I. Hendricks
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/* 
 * email:  sage.message@email.com
 * github: sage-etcher
 *
 */


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
#if !defined(DEBUG_MODE)
#define TRACE_MALLOC(size)       (malloc  (size))
#define TRACE_CALLOC(size,count) (calloc  (size, count))
#define TRACE_REALLOC(ptr,size)  (realloc (ptr,  size))
#define TRACE_FREE(ptr)          (free    (ptr))
#define TRACE_FOPEN(name,access) (fopen   (name, access))
#define TRACE_FCLOSE(file)       (fclose  (file))

#endif /* !defined(DEBUG_MODE) */


/* use custom functions if in debug mode */
#if defined(DEBUG_MODE)

/* where to log information to */
#undef DEBUG_LOG_TO_STDOUT
#define DEBUG_LOG_TO_LOGFILE

extern const char *debug_log_file;

/* log dynamic allocations and frees (to better find memory leaks */
#define TRACE_MALLOC(size)       (debug_malloc  (size,         __LINE__, __FILE__))
#define TRACE_CALLOC(size,count) (debug_calloc  (size, count,  __LINE__, __FILE__))
#define TRACE_REALLOC(ptr,size)  (debug_realloc (ptr,  size,   __LINE__, __FILE__))
#define TRACE_FREE(ptr)          (debug_free    (ptr,          __LINE__, __FILE__))
#define TRACE_FOPEN(name,access) (debug_fopen   (name, access, __LINE__, __FILE__))
#define TRACE_FCLOSE(file)       (debug_fclose  (file,         __LINE__, __FILE__))


/* debug logging functions */
void *debug_malloc  (size_t bytes, const int line_number, const char *source_file) WARN_UNUSED_RESULT;
void *debug_calloc  (size_t bytes, size_t count, const int line_number, const char *source_file) WARN_UNUSED_RESULT;
void *debug_realloc (void *ptr, size_t bytes, const int line_number, const char *source_file) WARN_UNUSED_RESULT;
void  debug_free    (void *ptr, const int line_number, const char *source_file);
FILE *debug_fopen   (const char *filename, const char *access_specifier, const int line_number, const char *source_file) WARN_UNUSED_RESULT;
int   debug_fclose  (FILE *fp, const int line_number, const char *source_file) WARN_UNUSED_RESULT;


#endif /* defined(DEBUG_MOD) */

#endif /* run once */


/* end of file */
