#include "pkg_conargs.h"

#include <stdio.h>
#include <string.h>

#include "pkg_debug.h"
#include "pkg_globals.h"
#include "pkg_log.h"


/* function prototypes */


/* function definitions */
void 
conarg_hello (void)
{
    (void)printf ("hello world\n");

    return;
}


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


static int
is_whitespace_char (char c)
{

    /* return 0 if the character is whitespace */
    switch (c)
    {
    case ' ':
    case '\t':
    case '\n':
    case '\r':
        return 0;
    }

    /* return 1 in all other cases */
    return 1;
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


/* returns the new index, index stays the same if no matches are found */
static int
get_long_commands (char **list, int index, int count)
{
    const char LONG_PREFIX[] = "--";
    char *arg= trim_whitespace (list[index]);

    /* all long commands start with the LONG_PREFIX (normally "--"), if the
     * given string doesn't, then we know that it is not a long command. */
    if (strncmp (arg, LONG_PREFIX, sizeof (LONG_PREFIX)) == 0)
    {
        goto get_long_commands_exit_0;
    }

    /* run through a large if-else chain to find out if we have a match. :/ */



get_long_commands_exit_0:
    TRACE_FREE (arg);
    return index;
}


static int
get_short_commands (char **list, unsigned index, unsigned count)
{

    return 0;
}


static void
get_packages (char **list, unsigned index, unsigned count)
{
    
    return;
}


void
conarg_settings (int argc, char **argv)
{
    int i, overhead;

    i = 1; /* start at the first arguement */
    for (; i < argc; i++)
    {
        /* check if the arguement matches one of the long commands */
        overhead = get_long_commands (argv, i, argc);
        if (overhead != i)
        {
            i = overhead;
            continue;
        }

        /* check if the arguement matches any unix style commands */
        if (get_short_commands (argv, i, argc) == 0)
            continue;

        /* if neither short or long command, assume the rest of the arguements
         * to be package names */ 
        get_packages (argv, i, argc);
        break;
    }
}


/* end of file */
