/* 
 * This source file is a part of the Leaf Package Manager.
 *
 * /source/log.c
 * Contains functions and constants needed for logging.
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

