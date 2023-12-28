/* 
 * This source file is a part of the Leaf Package Manager.
 * https://github.com/sage-etcher/leaf-pkg-manager
 *
 * /source/globals.c
 * Manages, initializes, and frees the program's global variables.
 *
 */

/* 
 * Copyright 2023-2024 Sage I. Hendricks
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

/* version message information */
const char *VERSION_MESSAGE = 
    "Leaf Package Manager 0.1.0-dev\n"
    "Copyright 2023 Sage I. Hendricks\n"
    "License Apache: The Apache version 2.0 license, <https://apache.org/licenses/LICENSE-2.0>.\n"
    "This is free software: you are free to change and redistribute it.\n"
    "There is NO WARRANTY, to the extent permitted by law.\n"
    "\n"
    "Written by Sage I. Hendricks.\n";

/* help message information */
const char *HELP_MESSAGE = 
    "Usage: pkg [OPTION]... [MODE] PACKAGE...\n"
    "       pkg [OPTION]... --create PACKAGE INSTALLPATH\n"
    "       pkg [OPTION]... --list [SEARCH]\n"
    "       pkg [OPTION]... --alias ALIAS PACKAGE\n"
    "       pkg [OPTION]... --remove-alias ALIAS...\n"
    "\n"
    "The PACKAGE argument is the full name of a local package or package alias.`\n"
    "\n"
    "The ALIAS arguement is the full name of specifically a package alias, and\n"
    "CANNOT be the name of a standard package\n"
    "\n"
    "The INSTALLPATH arguement is a path to where the program was installed,\n"
    "and is normally identical to the DESTDIR variable used when installing the\n"
    "program via make. The program must be installed into its own DESTDIR\n"
    "directory in order to be propperly made into a package\n"
    "\n"
    "The SEARCH argument is a regex string used to parse package names\n"
    "\n"
    "Mandatory arguments to long options are mandatory for short options too.\n"
    "Mode arguements are listed in the 'Usage' section above, please refer back\n"
    "to the section for help, default is the first line of Usage.\n"
    "Modes:\n"
    "  -a, --remove-alias         remove/unalias a package alias\n"
    "  -A, --alias                create a package alias (symlink) of a packge\n"
    "  -c, --create               create a package from an program installed using\n"
    "                             a (non-root) DESTDIR at make install\n"
    "  -C, --delete               permanently deletes the package, program must be\n"
    "                             recompiled and a news package must be made.\n"
    "                             delete is NOT the same as uninstall\n"
    "\n"
    "  -l, --list                 search through available packages. If no search\n"
    "                             string is given, list all locally available\n"
    "                             packages.\n"
    "\n"
    "  -S, --install              install an available package to the system\n"
    "  -s, --uninstall            uninstall a package from the system\n"
    "\n"
    "Options:\n" 
    "  -t, --use-config=FILE      specify an alternate config file for the program\n"
    "                             to use. note that the program automatically\n"
    "                             checks for a config file in the following order:\n"
    "                              1) FILE given here\n"
    "                              2) $XDG_CONFIG_HOME/lpkg/config.toml\n"
    "                              3) $HOME/.lpkg.toml\n"
    "                              4) /etc/lpkg/config.toml\n"
    "\n"
    "  -b, --brief                inverse of verbose, show only essential messages\n"
    "                             this is the default\n"
    "  -v, --verbose              show more, possibly unimportant, information\n"
    "\n"
    "  -h, --help                 show this message\n"
    "  -V, --version              show the copyright and licensing information\n"
    "\n"
    "The FILE argument is a path to a file, and is permitted to contain enviornment\n"
    "variables if need be. The expected file should be a cleanly formatted TOML,\n"
    "a default config file should have been installed at '/etc/lpkg/config.toml'.\n"
    "\n"
    "Exit status:\n"
    " 0  is default\n"
    " 1  if a minor problem occurs\n"
    " 2  if a fatal error is encountered\n"
    "\n"
    "Report bugs to: sage.message@email.com\n"
    "Leaf Package Manager home page: <https://github.com/sage-etcher/leaf-pkg-manager>\n"
    "General help using Leaf software: sage.message@email.com\n"; 

/* config file locations */
const char *XDG_CONFIG_FILE    = "${XDG_CONFIG_HOME}/lpkg/config.toml";
const char *HOME_CONFIG_FILE   = "${HOME}/.lpkg.toml";
const char *GLOBAL_CONFIG_FILE = "/etc/lpkg/config.toml";
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
mode   g_run_mode                = MODE_HELP_MSG; 
int    g_console_config_flag     = 0; 
char  *g_console_config_filename = NULL;
int    g_verbose_flag            = 0; 
int    g_help_flag               = 0; 
int    g_version_flag            = 0; 
char **g_arguments               = NULL;
size_t g_arguments_len           = 0;

/* default search strig for list */
const char *LIST_DEFAULT_SEARCH_STRING = ".*";

/* error logging strings constants */
err_msg WARNING_CANNOT_LOG_TO_FILE = "WARNING: cannot log to file\n";
err_msg ERROR_NO_HELP_FILE         = "ERROR: cannot find the help documentation file\n";
err_msg ERROR_NO_CONFIG_FILE       = "ERROR: cannot find config file\n";
err_msg ERROR_PARSING_TOML         = "ERROR: cannot parse TOML\n";

/* prompt messages */
const char *CONFIRM_INSTALL   = "You are about to install the following packages.";
const char *CONFIRM_UNINSTALL = "You are about to uninstall the following packages.";
const char *CONFIRM_DELETE    = "You are about to permanently remove the following packages.";
const char *CONFIRM_RMALIAS   = "You are about to remove the following package aliases.";



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
