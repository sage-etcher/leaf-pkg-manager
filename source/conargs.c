#include "conargs.h"

#include <stdio.h>
#include <string.h>

#include <getopt.h>

#include "debug.h"
#include "globals.h"
#include "log.h"


/* function prototypes */


/* function definitions */
void 
conarg_hello (void)
{
    (void)printf ("hello world\n");

    return;
}


#if defined(IGNORE)
/* move into a string utilities file */
static char *
string_array_join (char **list, size_t count, char *seperator)
{
    int i;

    size_t list_acc_size;
    size_t list_elem_length;

    size_t sep_length, sep_acc_size;

    char *result, *result_iter;
    size_t result_size;


    /* Iterate through each element of list, 
     * sum the length of each string into list_acc_size */
    list_acc_size = 0;
    for (i = 0; i < count; i++)
    {
        list_acc_size += strlen (list[i]);
    }

    /* Calculate the space needed to store n-1 seperators, where n is number of
     * elements in list */
    sep_length = strlen (seperator);
    sep_acc_size = ((count - 1) * sep_length);
   
    /* Result need's enough space for the accumulative string length of each
     * serperator and string in list. We can calculate and allocate the perfect
     * amount of space needed for result */
    result_size = list_acc_size + sep_acc_size;
    result = TRACE_MALLOC ((result_size + 1) * sizeof (char));
    assert (result != NULL);
    result_iter = result;

    /* Iterate through list, copying each string into restul_iter, then
     * append a seperator. Dont add a seperator for the last element. */
    for (i = 0; i < count; i++)
    {
        /* Calculate the length of the current element. */
        list_elem_length = strlen (list[i]);
       
        /* Apend the current string into result_iter, then iterate to the 
         * next string */
        (void)strncpy (result_iter, list[i], list_elem_length);
         
        /* If that was the last string in list, dont add a seperator */
        if ((i + 1) == count)
        {
            break;
        }

        /* Append a seperator after the most recent string */
        (void)strncpy ((result_iter+list_elem_length), seperator, sep_length);

        /* Move result_iter just past the new string and seperator */
        result_iter += (list_elem_length + sep_length);
    }

    /* Add the NULL terminator to the end of our result string */
    result[result_size] = '\0';

    /* Return the result string to the user */
    return result;
}


static char *
trim_whitespace (const char *source_str)
{
    char *base, *end;
    char *trimmed_string;
    size_t trimmed_len;

    /* Iterate through soruce_str until either a non-whitespace character is
     * found, or we reach the end of the string. */
    base = (char *)source_str;
    while ((*base != '\0')
           && (is_whitespace_char (*base++) != 0));

    /* Iterate through soruce_str back to front until either a non-whitespace
     * character is found, or we reach the base of the string. */
    end = (char *)source_str+strlen (source_str) - 1;
    while ((end >= base)
           && (is_whitespace_char (*end--) != 0));

    /* place the end ptr after the non-whitespace character */
    end++;

    /* copy the sub string into result */
    trimmed_len = end - base;
    trimmed_string = TRACE_MALLOC ((trimmed_len + 1) * sizeof (char));
    assert (trimmed_string != NULL);
    (void)strncpy (trimmed_string, base, trimmed_len);
    trimmed_string[trimmed_len] = '\0';

    /* return the trimmed string */
    return trimmed_string;
}
/* end move */
#endif /* defined(IGNORE) */


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
                g_help_flag = 1;
                break;

            case 'V': /* version */
                g_version_flag = 1;
                break;

            case '?': /* unrecognized command */
                /* getopt_long already threw an error message */
                break;

            default: /* AHHHHH */
                abort ();
        }
    }

    /* copy (by reference) extra arguements */
    g_arguments_len = argc - optind;
    g_arguments = argv + optind;

}


/* end of file */
