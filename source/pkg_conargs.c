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


void
conarg_settings (int argc, char **argv)
{
    char *arg_ptr;
    char *argv_string;

    /* Skip the first element of argv, then join the remaining elements into
     * a single string */
    argv_string = string_array_join (argv+1, argc - 1, " ");

    (void)printf ("%s\n", argv_string);

    /* Iterate through each character in argv_string */
    arg_ptr = argv_string;
    while (*arg_ptr != '\0')
    {
        /* (void)printf ("%p %c\n", arg_ptr, *arg_ptr); */

        /* move to the next character */
        arg_ptr++;
    }

    TRACE_FREE (argv_string);
}


/* end of file */
