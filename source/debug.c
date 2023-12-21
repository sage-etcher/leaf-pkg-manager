/* 
 * This source file is a part of the Leaf Package Manager.
 *
 * /source/debug.c
 * Contains functions and variables for debugging and testing.
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


#include "debug.h"

#include <stdio.h>
#include <malloc.h>

#include <assert.h>


/* wrapper */
#if defined(DEBUG_MODE)

/* log file to use */
const char *DEBUG_LOG_FILE = "pkgdebug.log";

/* file static variables/constants */ 
enum {
    DEBUG_ID_MALLOC,
    DEBUG_ID_CALLOC,
    DEBUG_ID_REALLOC,
    DEBUG_ID_FREE,
    DEBUG_ID_FOPEN,
    DEBUG_ID_FCLOSE
};

#define LOG_TEXT_MAXLEN 50
char g_log_text[LOG_TEXT_MAXLEN];


/* static function prototypes */
static void log_to_stream (FILE *stream, void *ptr, const char *log_text, const int line_number, const char *source_file);
static void log_to_file (const char *filename, void *ptr, const char *log_text, const int line_number, const char *source_file);
static void log_to_stdout (void *ptr, const char *log_text, const int line_number, const char *source_file);
static void log_cmd (void *ptr, const char *log_text, const int line_number, const char *source_file);


/* static functions */ 
static void
log_to_stream (FILE *stream, void *ptr, const char *log_text,
        const int line_number, const char *source_file)
{
    #if defined(DEBUG_LOG_TO_LOGFILE) || defined(DEBUG_LOG_TO_STDOUT)

    (void)fprintf (stream, "%p: %s: %s: %d\n",
            ptr, log_text, source_file, line_number);

    #endif /* defined(DEBUG_INFO_LOGFILE) || defined (DEBUG_INFO_STDOUT) */
}


static void
log_to_file (const char *filename, void *ptr, const char *log_text,
        const int line_number, const char *source_file)
{
    #if defined(DEBUG_LOG_TO_LOGFILE)

    FILE *fp;

    /* try to open the file */
    fp = fopen (filename, "a+");
    if (fp == NULL)
    {
        /* if the file cannot be opened, throw a warning to stderr */
        (void)fprintf (stderr, "DEBUG WARNING: couldn't open the log file\n");
        return;
    }

    /* otherwise, if the file was opened, log_cmd to it */
    log_to_stream (fp, ptr, log_text, line_number, source_file);

    /* close the file */
    fclose (fp);
   
    #endif /* defined(DEBUG_INFO_LOGFILE) */
}


static void
log_to_stdout (void *ptr, const char *log_text, const int line_number,
        const char *source_file)
{
    #if defined(DEBUG_LOG_TO_STDOUT)

    /* log to stdout buffer */
    log_to_stream (stdout, ptr, log_text, line_number, source_file);

    /* flush the stdout buffer to counteract an issue with bash */
    fflsuh (stdout);

    #endif /* defined(DEBUG_INFO_STDOUT) */
}


static void
log_cmd (void *ptr, const char *log_text, const int line_number,
        const char *source_file)
{
    log_to_stdout (ptr, log_text, line_number, source_file);
    log_to_file (DEBUG_LOG_FILE, ptr, log_text, line_number, source_file);
}


/* gloabl functions */
void *
debug_malloc (size_t bytes, const int line_number, const char *source_file)
{
    void *new_ptr;

    /* reallocate the ptr */
    new_ptr = malloc (bytes);
    assert (new_ptr != NULL);

    /* log the operation */
    (void)snprintf (g_log_text, LOG_TEXT_MAXLEN, "%d: malloc (%lu)", 
                    DEBUG_ID_MALLOC, bytes);
    log_cmd (new_ptr, g_log_text, line_number, source_file);

    /* return the new pointer */
    return new_ptr;
}


void *
debug_calloc (size_t bytes, size_t count,
        const int line_number, const char *source_file)
{
    void *new_ptr;

    /* reallocate the ptr */
    new_ptr = calloc (bytes, count);

    /* log the operation */
    (void)snprintf (g_log_text, LOG_TEXT_MAXLEN, "%d: calloc (%lu, %lu)", 
                    DEBUG_ID_CALLOC, bytes, count);
    log_cmd (new_ptr, g_log_text, line_number, source_file);

    /* return the new pointer */
    return new_ptr;
}


void *
debug_realloc (void *ptr, size_t bytes, const int line_number, 
        const char *source_file)
{
    void *new_ptr;

    /* reallocate the ptr */
    new_ptr = realloc (ptr, bytes);

    /* log the operation */
    (void)snprintf (g_log_text, LOG_TEXT_MAXLEN, "%d: realloc (%p, %lu)", 
                    DEBUG_ID_REALLOC, ptr, bytes);
    log_cmd (new_ptr, g_log_text, line_number, source_file);

    /* return the new pointer */
    return new_ptr;
}


void
debug_free (void *ptr, const int line_number, const char *source_file)
{
    /* free the ptr */
    free (ptr);

    /* log_cmd the operation */
    (void)snprintf (g_log_text, LOG_TEXT_MAXLEN, "%d: free (%p)", 
                    DEBUG_ID_FREE, ptr);
    log_cmd (ptr, g_log_text, line_number, source_file);

    return;
}


FILE *
debug_fopen (const char *filename, const char *access_specifier,
        const int line_number, const char *source_file)
{
    FILE *open_file;

    /* reallocate the ptr */
    open_file = fopen (filename, access_specifier);

    /* log the operation */
    (void)snprintf (g_log_text, LOG_TEXT_MAXLEN, "%d: fopen (\"%s\", \"%s\")",
                    DEBUG_ID_FOPEN, filename, access_specifier);
    log_cmd (open_file, g_log_text, line_number, source_file);

    /* return the new pointer */
    return open_file;
}


int
debug_fclose (FILE *fp, const int line_number, const char *source_file)
{
    int return_value;

    /* reallocate the ptr */
    return_value = fclose (fp);

    /* log the operation */
    (void)snprintf (g_log_text, LOG_TEXT_MAXLEN, "%d: fclose (%p)",
                    DEBUG_ID_FCLOSE, fp);
    log_cmd (fp, g_log_text, line_number, source_file);

    /* return the new pointer */
    return return_value;
}


/* end of DEBUG_MODE wrapper */
#endif /* defined(DEBUG_MODE) */
