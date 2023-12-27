/* 
 * This source file is a part of the Leaf Package Manager.
 *
 * /source/instruction.c
 * Redirect execution depending on the given instruction.
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


#include "fileio.h"
#include "string-ext.h"
#include "instruction.h"

#include "globals.h"
#include "log.h"

#include "mode-list.h"
#include "mode-alias.h"
#include "mode-create.h"
#include "mode-delete.h"
#include "mode-install.h"
#include "mode-uninstall.h"
#include "mode-remove-alias.h"

#include "debug.h"
#include <assert.h>


/* static-function prototypes */
static int get_confirmation (const char *base_prompt, char *details);
static void list_wrapper (void);
static void alias_wrapper (void);
static void create_wrapper (void);
static void delete_wrapper (void);
static void install_wrapper (void);
static void uninstall_wrapper (void);
static void remove_alias_wrapper (void);


/* functions */
void
inst_execute (int mode)
{
    switch (mode)
    {
    case MODE_LIST:
        list_wrapper ();
        break;

    case MODE_ALIAS:
        alias_wrapper ();
        break;

    case MODE_CREATE:
        create_wrapper ();
        break;

    case MODE_DELETE:
        delete_wrapper ();
        break;

    case MODE_INSTALL:
        install_wrapper ();
        break;

    case MODE_UNINSTALL:
        uninstall_wrapper ();
        break;

    case MODE_REMOVE_ALIAS:
        remove_alias_wrapper ();
        break;

    default: /* fatal error */
        abort ();
    }

    return;
}


static void
install_wrapper (void)
{
    int error_code, confirmation;
    char **package_list, *package_name, *joined_package_list;
    size_t n_packages, i;

    /* check that propper # of params were given */
    if (g_arguments_len < ARGC_MIN_INSTALL)
    {
        /* imporpper # of arguementsd */
        /* log an error and quit */
        return;
    }

    /* get the parameters */
    package_list = g_arguments;
    n_packages   = g_arguments_len;

    /* confirm that the user wants to do this */
    joined_package_list = string_array_join (package_list, n_packages, ", ");
    confirmation = get_confirmation (CONFIRM_INSTALL, joined_package_list);
    TRACE_FREE (joined_package_list);
    if (confirmation == EXIT_FAILURE)
    {
        /* exit without doing anything */
        return;
    }

    /* execute the instruction */
    for (i = 0; i < n_packages; i++)
    {
        package_name = package_list[i];

        error_code = install_package (package_name);

        if (error_code != EXIT_SUCCESS)
        {
            /* log an error */
            /* abort execution */
            break;
        }
    }

    return;
}


static void
uninstall_wrapper (void)
{
    int error_code, confirmation;
    char **package_list, *package_name, *joined_package_list;
    size_t n_packages, i;

    /* check that propper # of params were given */
    if (g_arguments_len < ARGC_MIN_UNINSTALL)
    {
        /* imporpper # of arguementsd */
        /* log an error and quit */
        return;
    }

    /* get the parameters */
    package_list = g_arguments;
    n_packages   = g_arguments_len;

    /* confirm that the user wants to do this */
    joined_package_list = string_array_join (package_list, n_packages, ", ");
    confirmation = get_confirmation (CONFIRM_UNINSTALL, joined_package_list);
    TRACE_FREE (joined_package_list);
    if (confirmation == EXIT_FAILURE)
    {
        /* exit without doing anything */
        return;
    }

    /* execute the instruction */
    for (i = 0; i < n_packages; i++)
    {
        package_name = package_list[i];

        error_code = uninstall_package (package_name);
        if (error_code != EXIT_SUCCESS)
        {
            /* log an error */
            /* abort execution */
            break;
        }
    }

    return;
}


static void
create_wrapper (void)
{
    char *package_name, *fakeroot_path;

    /* check that propper # of params were given */
    if (g_arguments_len != ARGC_ABS_CREATE)
    {
        /* imporpper # of arguementsd */
        /* log an error and quit */
        return;
    }

    /* get the parameters */
    package_name  = g_arguments[CREATE_PKGNAME_INDEX];
    fakeroot_path = expand_env_i (g_arguments[CREATE_FAKEROOT_INDEX]);

    /* execute the instruction */
    create_package (package_name, fakeroot_path);


    TRACE_FREE (fakeroot_path);
    return;
}


static void
delete_wrapper (void)
{
    int error_code, confirmation;
    char **package_list, *package_name, *joined_package_list;
    size_t n_packages, i;

    /* check that propper # of params were given */
    if (g_arguments_len < ARGC_MIN_DELETE)
    {
        /* imporpper # of arguementsd */
        /* log an error and quit */
        return;
    }

    /* get the parameters */
    package_list = g_arguments;
    n_packages   = g_arguments_len;

    /* confirm that the user wants to do this */
    joined_package_list = string_array_join (package_list, n_packages, ", ");
    confirmation = get_confirmation (CONFIRM_DELETE, joined_package_list);
    TRACE_FREE (joined_package_list);
    if (confirmation == EXIT_FAILURE)
    {
        /* exit without doing anything */
        return;
    }

    /* execute the instruction */
    for (i = 0; i < n_packages; i++)
    {
        package_name = package_list[i];

        error_code = delete_package (package_name);
        if (error_code != EXIT_SUCCESS)
        {
            /* log an error */
            /* abort execution */
            break;
        }
    }

    return;
}


static void
alias_wrapper (void)
{
    char *src, *dst;

    /* check that propper # of params were given */
    if (g_arguments_len != ARGC_ABS_ALIAS)
    {
        /* imporpper # of arguementsd */
        /* log an error and quit */
        return;
    }

    /* get the parameters */
    src = g_arguments[ALIAS_SRC_INDEX];
    dst = g_arguments[ALIAS_DST_INDEX];

    /* execute the instruction */
    alias_package (src, dst);

    return;
}


static void
remove_alias_wrapper (void)
{
    int error_code, confirmation;
    char **package_list, *package_name, *joined_package_list;
    size_t n_packages, i;

    /* check that propper # of params were given */
    if (g_arguments_len < ARGC_MIN_RMALIAS)
    {
        /* imporpper # of arguementsd */
        /* log an error and quit */
        return;
    }

    /* get the parameters */
    package_list = g_arguments;
    n_packages   = g_arguments_len;

    /* confirm that the user wants to do this */
    joined_package_list = string_array_join (package_list, n_packages, ", ");
    confirmation = get_confirmation (CONFIRM_RMALIAS, joined_package_list);
    TRACE_FREE (joined_package_list);
    if (confirmation == EXIT_FAILURE)
    {
        /* exit without doing anything */
        return;
    }

    /* execute the instruction */
    for (i = 0; i < n_packages; i++)
    {
        package_name = package_list[i];

        error_code = remove_alias (package_name);
        if (error_code != EXIT_SUCCESS)
        {
            /* log an error */
            /* abort execution */
            break;
        }
    }

    return;
}


static void
list_wrapper (void)
{
    char *search_string = NULL;

    /* where the propper # of parameters given for the isntruction? */
    if ((g_arguments_len > ARGC_MAX_LIST)
        || (g_arguments_len < ARGC_MIN_LIST))
    {
        /* impropper # of arguements */
        /* log an error and quit */
        return;
    }

    /* get the parameters */
    if (g_arguments_len == ARGC_MIN_LIST)
    {
        /* if no arguement is given, use default search string */
        search_string = (char *)LIST_DEFAULT_SEARCH_STRING;
    }
    else if (g_arguments_len == ARGC_MAX_LIST)
    {
        /* if an argument is given, use it as a search string */
        search_string = g_arguments[LIST_SRCH_INDEX];
    }

    /* execute the instruction */
    list_packages (search_string);

    return;
}


static int
get_confirmation (const char *base_prompt, char *details)
{
    char user_input, lower;

    /* print the prompt */
    printf ("%s (%s)\nContinue [Y/n]? ", base_prompt, details);

    /* get a character from the user */
    scanf("%1c", &user_input);
   
    /* interpret the result */
    lower = tolower (user_input);
    if (lower == 'n')
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}


/* end of file */
