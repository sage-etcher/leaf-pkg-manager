/* 
 * This source file is a part of the Leaf Package Manager.
 * https://github.com/sage-etcher/leaf-pkg-manager
 *
 * /source/conargs.c
 * Contains functions for proccessing terminal arguments and flags.
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


#include "conargs.h"

#include <stdlib.h>
#include <getopt.h>

#include "globals.h"


/* function prototypes */


/* function definitions */
void
conarg_settings (int argc, char **argv)
{
    int c;
    int option_index;
    const struct option long_options[] =
    {
        /* name,           arg?,               flag*,  return */
        { "install",       no_argument,        0,      'S' },
        { "uninstall",     no_argument,        0,      's' },
        { "create",        no_argument,        0,      'C' },
        { "delete",        no_argument,        0,      'c' },
        { "alias",         no_argument,        0,      'A' },
        { "remove-alias",  no_argument,        0,      'a' },
        { "list",          no_argument,        0,      'l' },
        { "use-config",    required_argument,  0,      't' },
        { "verbose",       no_argument,        0,      'v' },
        { "brief",         no_argument,        0,      'b' },
        { "help",          no_argument,        0,      'h' },
        { "version",       no_argument,        0,      'V' },
        { 0, 0, 0, 0 }
    };


    /* get command list */
    while (1)
    {
        /* reset the option index */
        option_index = 0;
    
        /* get command */
        c = getopt_long (argc, argv, "SsCcAalt:vbhV",
                         long_options, &option_index);
      
        /* if there are no more options, stop looping */
        if (c == -1)
        {
            break;
        }

        /* switch statement for different options */
        switch (c)
        {
            case 0: /* flag already set */
                break;

            case 'S': /* install */
                g_run_mode = MODE_INSTALL;
                break;

            case 's': /* uninstall */
                g_run_mode = MODE_UNINSTALL;
                break;

            case 'C': /* create */
                g_run_mode = MODE_CREATE;
                break;

            case 'c': /* delete */
                g_run_mode = MODE_DELETE;
                break;

            case 'A': /* alias */
                g_run_mode = MODE_ALIAS;
                break;

            case 'a': /* remove-alias */
                g_run_mode = MODE_REMOVE_ALIAS;
                break;

            case 'l': /* list */
                g_run_mode = MODE_LIST;
                break;

            case 't': /* use-config */
                g_console_config_flag = 1;
                g_console_config_filename = optarg;
                break;

            case 'v': /* verbose */
                g_verbose_flag = 1;
                break;

            case 'b': /* brief */
                g_verbose_flag = 0;
                break;

            case 'h': /* help */
                g_run_mode = MODE_HELP_MSG;
                /* stop checking for arguments */
                return;

            case 'V': /* version */
                g_run_mode = MODE_VERSION_MSG;
                /* stop checking for arguments */
                return;

            case '?': /* unrecognized command */
                /* getopt_long already threw an error message */
                g_run_mode = MODE_HELP_MSG;     /* print help message */
                /* stop checking for arguments */
                return;

            default: /* AHHHHH code mistake */
                abort ();
        }
    }

    /* copy (by reference) extra arguements */
    g_arguments_len = argc - optind;
    g_arguments = argv + optind;

}


/* end of file */
