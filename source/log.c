#include "log.h"

#include <stdio.h>

#include "debug.h"
#include "fileio.h"
#include "globals.h"


/* globals */
err_msg WARNING_CANNOT_LOG_TO_FILE = "WARNING: cannot log to file\n";
err_msg ERROR_NO_CONFIG_FILE = "ERROR: cannot find config file\n";
err_msg ERROR_PARSING_TOML   = "ERROR: cannot parse TOML\n";


/* static function prototypes */


/* functions */
void
log_message (const char *msg)
{
    (void)log_to_file (g_config_log_file, msg);
    log_to_term (stderr, msg);

    return;
}


int
log_to_file (const char *log_file, const char *msg)
{
    int exit_code;
    exit_code = file_append (log_file, msg);

    if (exit_code != 0)
    {
        log_to_term (stderr, WARNING_CANNOT_LOG_TO_FILE);
    }

    return exit_code;
}


void
log_to_term (FILE *stream, const char *msg)
{
    (void)fprintf (stream, "%s", msg);

    return;
}

