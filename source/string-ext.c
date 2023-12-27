/* 
 * This source file is a part of the Leaf Package Manager.
 * https://github.com/sage-etcher/leaf-pkg-manager
 *
 * /source/string-ext.c
 * An extended set of functions for working with and manipulating strings.
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


#include "string-ext.h"

#include <ctype.h>
#include <string.h>
#include <assert.h>

#include "debug.h"


/* function prototypes */


/* function definitions */
char *
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


char *
trim_whitespace (const char *source_str)
{
    char *base, *end;
    char *trimmed_string;
    size_t trimmed_len;

    /* Iterate through soruce_str until either a non-whitespace character is
     * found, or we reach the end of the string. */
    base = (char *)source_str;
    while ((*base != '\0')
           && (isspace (*base++) != 0));

    /* Iterate through soruce_str back to front until either a non-whitespace
     * character is found, or we reach the base of the string. */
    end = (char *)source_str+strlen (source_str) - 1;
    while ((end >= base)
           && (isspace (*end--) != 0));

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


/* end of file */
