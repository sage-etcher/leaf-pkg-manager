#include "pkg_debug.h"

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#ifdef DEBUG_MODE
const char *DEBUG_LOG_FILE = "pkgdebug.log";


enum {
    DEBUG_ID_MALLOC,
    DEBUG_ID_CALLOC,
    DEBUG_ID_REALLOC,
    DEBUG_ID_FREE,
    DEBUG_ID_FOPEN,
    DEBUG_ID_FCLOSE
};


static void *
debug_log_to_file (int id, void *ptr, void *ptr_two, size_t x, size_t y, const int line, const char *file)
{
    FILE *fp = NULL;
    void *new_ptr = NULL;

    /* do the thing */
    switch (id)
    {
    case DEBUG_ID_MALLOC:
        new_ptr = malloc (x);
        break;
    case DEBUG_ID_CALLOC:
        new_ptr = calloc (x, y);
        break;
    case DEBUG_ID_REALLOC:
        new_ptr = realloc (ptr, x);
        break;
    case DEBUG_ID_FREE:
        free (ptr);
        break;
    case DEBUG_ID_FOPEN:
        new_ptr = fopen ((const char *)ptr, (const char *)ptr_two);
        break;
    case DEBUG_ID_FCLOSE:
        *(int *)ptr_two = fclose ((FILE *)ptr);
        break;
    }

    /* log thing to console */
    #ifdef DEBUG_INFO_STDOUT
    switch (id)
    {
    case DEBUG_ID_MALLOC:
        (void)fprintf (stdout, "%p: %d: malloc (%lu): %s: %d\n", 
                new_ptr, id, x, file, line);
        break;
    case DEBUG_ID_CALLOC:
        (void)fprintf (stdout, "%p: %d: calloc (%lu, %lu): %s: %d\n", 
                new_ptr, id, x, y, file, line);
        break;
    case DEBUG_ID_REALLOC:
        (void)fprintf (stdout, "%p: %d: realloc (%p, %lu): %s: %d\n", 
                new_ptr, id, ptr, x, file, line);
        break;
    case DEBUG_ID_FREE:
        (void)fprintf (stdout, "%p: %d: free (%p): %s: %d\n", 
                ptr, id, ptr, file, line);
        break;
    case DEBUG_ID_FOPEN:
        (void)fprintf (stdout, "%p: %d: fopen (\"%s\", \"%s\"): %s: %d\n", 
                new_ptr, id, (const char *)ptr, (const char *)ptr_two, file, line);
        break;
    case DEBUG_ID_FCLOSE:
        (void)fprintf (stdout, "%p: %d: fclose (%p): %s: %d\n", 
                ptr, id, ptr, file, line);
        break;
    }
    #endif /* def DEBUG_INFO_STDOUT */

    /* log thing to file */
    #ifdef DEBUG_INFO_LOGFILE
    fp = fopen (DEBUG_LOG_FILE, "a+");

    if (fp != NULL)
    {
        switch (id)
        {
        case DEBUG_ID_MALLOC:
            (void)fprintf (fp, "%p: %d: malloc (%lu): %s: %d\n", 
                    new_ptr, id, x, file, line);
            break;
        case DEBUG_ID_CALLOC:
            (void)fprintf (fp, "%p: %d: calloc (%lu, %lu): %s: %d\n", 
                    new_ptr, id, x, y, file, line);
            break;
        case DEBUG_ID_REALLOC:
            (void)fprintf (fp, "%p: %d: realloc (%p, %lu): %s: %d\n", 
                    new_ptr, id, ptr, x, file, line);
            break;
        case DEBUG_ID_FREE:
            (void)fprintf (fp, "%p: %d: free (%p): %s: %d\n", 
                    ptr, id, ptr, file, line);
            break;
        case DEBUG_ID_FOPEN:
            (void)fprintf (fp, "%p: %d: fopen (\"%s\", \"%s\"): %s: %d\n", 
                    new_ptr, id, (const char *)ptr, (const char *)ptr_two, file, line);
            break;
        case DEBUG_ID_FCLOSE:
            (void)fprintf (fp, "%p: %d: fclose (%p): %s: %d\n", 
                    ptr, id, ptr, file, line);
            break;
        }

        fclose (fp);
    }
    #endif /* def DEBUG_INFO_LOGFILE */

    /* return the new ptr */
    return new_ptr;
}

void *
debug_log_malloc (size_t size, const int line, const char *file)
{
    return debug_log_to_file (DEBUG_ID_MALLOC, NULL, NULL, size, 0, line, file);
}


void *
debug_log_calloc (size_t size, size_t num, const int line, const char *file)
{
    return debug_log_to_file (DEBUG_ID_CALLOC, NULL, NULL, size, num, line, file);
}


void *
debug_log_realloc (void *ptr, size_t size, const int line, const char *file)
{
    return debug_log_to_file (DEBUG_ID_REALLOC, ptr, NULL, size, 0, line, file);
}


void
debug_log_free (void *ptr, const int line, const char *file)
{
    (void)debug_log_to_file (DEBUG_ID_FREE, ptr, NULL, 0, 0, line, file);
    return;
}


FILE *
debug_log_fopen (const char *filename, const char *open_type, const int line, const char *file)
{
    return debug_log_to_file (DEBUG_ID_FOPEN, (char *)filename, (char *)open_type, 0, 0, line, file);
}


int
debug_log_fclose (FILE *fp, const int line, const char *file)
{
    int return_value;
    (void)debug_log_to_file (DEBUG_ID_FCLOSE, fp, &return_value, 0, 0, line, file);
    return return_value;
}
#endif /* def DEBUG_MODE */
