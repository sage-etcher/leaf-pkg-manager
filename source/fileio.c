#include "fileio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <assert.h>

#include "debug.h"


/* function prototypes */


/* function definitions */
int
file_exists (const char * restrict filepath)
{
	FILE *fp;

	/* try to open the file */
	fp = TRACE_FOPEN (filepath, "r");
	/* if fopen succeeds, close the file, and return a success */ 
	if (fp != NULL)
	{
		(void)TRACE_FCLOSE (fp);
		return (1);
	}

	/* otherwise, if the command fails, return a failures */
	return (0);
}


char *
expand_enviornment_variable (const char *s, int *expanded_flag)
{
    /* size storeage for fake substrings, used to avoid repeated subtraction */
    size_t result_size, value_size, env_size, pre_size, post_size;

    char *pre_start,  *pre_end;     /* string before enviornment variable */
    char *post_start, *post_end;    /* string after enviornment variable */
    char *env_start,  *env_end;     /* enviornment variable */

    char *env_substr;               /* substring of the enviornment variable */
    char *result, *result_iter;     /* result variable */

    const char *value;              /* expanded enviornment variable */


    /* get prefix "substr" */
    pre_start = (char *)s;
    pre_end   = strstr (s, "${");

    if (pre_end == NULL)
    {
        *expanded_flag = -1;
        
        result = TRACE_MALLOC ((strlen (s) + 1) * sizeof (char));
        assert (result != NULL);
        (void)strcpy (result, s);

        return result;
    }

    pre_size  = pre_end - pre_start;

    /* get the enviornment variable "substr" */
    env_start = pre_end+2;  /* not a memory leak, if EOS will start on '\0' */
    env_end   = strstr (env_start, "}");

    if (env_end == NULL)
    {
        *expanded_flag = -1;
        
        result = TRACE_MALLOC ((strlen (s) + 1) * sizeof (char));
        assert (result != NULL);
        (void)strcpy (result, s);

        return result;
    } 

    env_size  = env_end - env_start;

    env_substr = TRACE_MALLOC ((env_size + 1) * sizeof (char));
    assert (env_substr != NULL);
    (void)strncpy (env_substr, env_start, env_size);
    env_substr[env_size] = '\0';

    /* get suffix "substr" */
    post_start = env_end+1; /* not a mem leak, if EOS will start on '\0' */
    post_end   = (char *)(s + strlen (s));

    post_size = post_end - post_start;

    /* expand the enviornment variable */
    value = getenv (env_substr);
    if (value == NULL)
        value = "";

    value_size = strlen (value);

    /* concatenate results into result */
    result_size = pre_size + value_size + post_size;
    result = TRACE_MALLOC ((result_size + 1) * sizeof (char));
    assert (result != NULL);
    result_iter = result;
 
    /* concatenate prefix to result */
    (void)strncpy (result_iter, pre_start, pre_size);
    result_iter += pre_size;

    /* concatenate value to result */
    (void)strncpy (result_iter, value, value_size);
    result_iter += value_size;

    /* concatenate suffex to result */
    (void)strncpy (result_iter, post_start, post_size);
    result_iter += post_size;

    /* add null terminator */
    *(result_iter++) = '\0';

    /* free the substring from earlier */
    TRACE_FREE (env_substr);

    /* return that a variable was expanded, and the result */
    *expanded_flag = 0;
    return result;
}


char *
expand_enviornment_variables_iterative (const char *s)
{
    int expanded_env;
    char *result, *overhead;

    /* first pass use the given string */
    result = expand_enviornment_variable (s, &expanded_env);
    
    /* while expand_enviornment_variable keeps expanding more variables */
    while (expanded_env == 0)
    {
        /* expand the next variable */
        overhead = expand_enviornment_variable(result, &expanded_env);

        /* if it succeeds, copy the new value into result */
        if (expanded_env == 0)
        {
            TRACE_FREE (result);
            result = overhead;
        }
        else
        {
            TRACE_FREE (overhead);
        }
    }

    /* return the result string, with all enviornment variables expanded */
    return result;
}


size_t
file_text_size (FILE * restrict fp)
{
	size_t file_pos, file_size;

	/* save the stream's position */
	file_pos = ftell (fp);

	/* goto the end of the stream and get the offset */
	(void)fseek (fp, 0L, SEEK_END);
	file_size = ftell (fp);
	
	/* restore the stream's position */
	(void)fseek (fp, file_pos, SEEK_SET);

	/* return size of the given stream */
	return file_size;
}

char *
file_read_content (const char * restrict filepath)
{
	FILE * restrict fp = NULL;
	char * restrict content = NULL;
	size_t content_size; 

	/* open the file */
	fp = TRACE_FOPEN (filepath, "r");
	if (fp == NULL)
		return NULL;

	/* get size of content */
	content_size = file_text_size (fp);
	content = (char * restrict)TRACE_MALLOC (content_size);
    assert (content != NULL);

	/* read data from the file into content */
	(void)fgets (content, content_size, fp);

	/* close the file and exit */
	(void)TRACE_FCLOSE (fp);
	return content;
}


int
file_append (const char *filename, const char *data)
{
    FILE *fp;

    fp = TRACE_FOPEN (filename, "a+");
    if (fp == NULL)
        return -1;

    (void)fprintf (fp, "%s", data); 

    (void)TRACE_FCLOSE (fp);

    return 0;
}


/* end of file */
