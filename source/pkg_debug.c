#include "pkg_debug.h"

#include <stdio.h>
#include <malloc.h>
#include <assert.h>


const char *DEBUG_LOG_FILE = "pkgdebug.log";


void *
debug_log_malloc (size_t size, const int line, const char *file)
{
    FILE *fp;
    void *new_ptr;

    /* allocate data */
    new_ptr = malloc (size);
    assert (new_ptr != NULL);

#ifdef DEBUG_INFO_STDOUT
    /* log to stdout */
    (void)fprintf (stdout, "%p: %s: %d: 0: malloc (%lu)\n", new_ptr, file, line, size);
#endif /* def DEBUG_INFO_STDOUT */

#ifdef DEBUG_INFO_LOGFILE
    /* log to file */
    fp = fopen (DEBUG_LOG_FILE, "a+");
    if (fp != NULL)
    {
        (void)fprintf (fp, "%p: %s: %d: 0: malloc (%lu)\n", new_ptr, file, line, size);
        (void)fclose(fp);
    }
    else
    {
        fprintf (stderr, "DEBUG WARNING: could not open debug log file %s\n", DEBUG_LOG_FILE);
    }
#endif /* def DEBUG_INFO_LOGFILE */

    /* return the new ptr */
    return new_ptr;
}


void *
debug_log_calloc (size_t size, size_t num, const int line, const char *file)
{
    FILE *fp;
    void *new_ptr;

    /* allocate data */
    new_ptr = calloc (size, num);
    assert (new_ptr != NULL);

#ifdef DEBUG_INFO_STDOUT
    /* log to stdout */
    (void)fprintf (stdout, "%p: %s: %d: 1: calloc (%lu, %lu)\n", new_ptr, file, line, size, num);
#endif /* def DEBUG_INFO_STDOUT */

#ifdef DEBUG_INFO_LOGFILE
    /* log to file */
    fp = fopen (DEBUG_LOG_FILE, "a+");
    if (fp != NULL)
    {
        (void)fprintf (fp, "%p: %s: %d: 1: calloc (%lu, %lu)\n", new_ptr, file, line, size, num);
        (void)fclose(fp);
    }
    else
    {
        fprintf (stderr, "DEBUG WARNING: could not open debug log file %s\n", DEBUG_LOG_FILE);
    }
#endif /* def DEBUG_INFO_LOGFILE */

    /* return the new ptr */
    return new_ptr;
}


void *
debug_log_realloc (void *ptr, size_t size, const int line, const char *file)
{
    FILE *fp;
    void *new_ptr;

    /* allocate data */
    new_ptr = realloc (ptr, size);
    assert (new_ptr != NULL);

#ifdef DEBUG_INFO_STDOUT
    /* log to stdout */
    (void)fprintf (stdout, "%p: %s: %d: 2: realloc (%p, %lu)\n", new_ptr, file, line, ptr, size);
#endif /* def DEBUG_INFO_STDOUT */

#ifdef DEBUG_INFO_LOGFILE
    /* log to file */
    fp = fopen (DEBUG_LOG_FILE, "a+");
    if (fp != NULL)
    {
        (void)fprintf (fp, "%p: %s: %d: 2: realloc (%p, %lu)\n", new_ptr, file, line, ptr, size);
        (void)fclose(fp);
    }
    else
    {
        fprintf (stderr, "DEBUG WARNING: could not open debug log file %s\n", DEBUG_LOG_FILE);
    }
#endif /* def DEBUG_INFO_LOGFILE */

    /* return the new ptr */
    return new_ptr;
}


void
debug_log_free (void *ptr, const int line, const char *file)
{
    FILE *fp;

#ifdef DEBUG_INFO_STDOUT
    /* log to stdout */
    (void)fprintf (stdout, "%p: %s: %d: 3: free (%p)\n", ptr, file, line, ptr);
#endif /* def DEBUG_INFO_STDOUT */

#ifdef DEBUG_INFO_LOGFILE
    /* log to file */
    fp = fopen (DEBUG_LOG_FILE, "a+");
    if (fp != NULL)
    {
        (void)fprintf (fp, "%p: %s: %d: 3: free (%p)\n", ptr, file, line, ptr);
        (void)fclose(fp);
    }
    else
    {
        fprintf (stderr, "DEBUG WARNING: could not open debug log file %s\n", DEBUG_LOG_FILE);
    }
#endif /* def DEBUG_INFO_LOGFILE */

    /* free the pointer */
    free (ptr);

    return;
}


