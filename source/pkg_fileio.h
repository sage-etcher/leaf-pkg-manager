/* run once */
#pragma once
#ifndef __PKG_FILEIO_HEADER__
#define __PKG_FILEIO_HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <assert.h>


/* functions prototypes */
char *expand_enviornment_variable (const char *s, int *expanded_flag);
char *expand_enviornment_variables_iterative (const char *s);

int file_exists (const char *filepath);
int file_append (const char *filepath, const char *data);
char *file_read_content (const char *filepath);


#endif /* run once */
