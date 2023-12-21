/* 
 * This source file is a part of the Leaf Package Manager.
 *
 * /source/globals.c
 * Manages, initializes, and frees the program's global variables.
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


#include "globals.h"

#include <malloc.h>

#include "debug.h"

/* config file locations */
const char *XDG_CONFIG_FILE    = "${XDG_CONFIG_HOME}/pkg/config.toml";
const char *HOME_CONFIG_FILE   = "${HOME}/.pkg.toml";
const char *GLOBAL_CONFIG_FILE = "/etc/pkg/config.toml";
/* selected config file to use (points to one the above) */
char *g_config_file;

/* TOML keys/tables */
const char *CONFIG_TABLE_GENERAL     = "general";
const char *CONFIG_KEY_DBFILE        = "database_file";
const char *CONFIG_KEY_LOCALPKGPATH  = "local_package_path";
const char *CONFIG_KEY_INSTALLPREFIX = "install_prefix";
const char *CONFIG_KEY_EXTRACTPATH   = "extract_path";
const char *CONFIG_KEY_LOGFILE       = "log_file";
/* where the data gets stored */
char *g_config_database_file;
char *g_config_local_package_path;
char *g_config_install_prefix;
char *g_config_extract_path;
char *g_config_log_file;

/* console parameter variables/flags */
mode   g_run_mode                = MODE_LIST; 
int    g_console_config_flag     = 0; 
char  *g_console_config_filename = NULL;
int    g_verbose_flag            = 0; 
int    g_help_flag               = 0; 
int    g_version_flag            = 0; 
char **g_arguments               = NULL;
size_t g_arguments_len           = 0;

/* error logging strings constants */
err_msg WARNING_CANNOT_LOG_TO_FILE = "WARNING: cannot log to file\n";
err_msg ERROR_NO_CONFIG_FILE = "ERROR: cannot find config file\n";
err_msg ERROR_PARSING_TOML   = "ERROR: cannot parse TOML\n";




/* function prototypes */
static void free_config (void);


/* functions */
void
global_cleanup (void)
{
    /* clean up config settings */
    free_config ();
    TRACE_FREE (g_config_file);
}
    

static void 
free_config (void)
{
    TRACE_FREE (g_config_database_file);
    TRACE_FREE (g_config_local_package_path);
    TRACE_FREE (g_config_install_prefix);
    TRACE_FREE (g_config_extract_path);
    TRACE_FREE (g_config_log_file);

    return;
}


/* end of file */
