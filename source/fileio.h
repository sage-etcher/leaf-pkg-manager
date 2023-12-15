/* run once */
#pragma once
#ifndef __PKG_FILEIO_HEADER__
#define __PKG_FILEIO_HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <assert.h>

#include "debug.h"


/* functions prototypes */
char *expand_enviornment_variable (const char *s, int *expanded_flag) WARN_UNUSED_RESULT;
char *expand_enviornment_variables_iterative (const char *s) WARN_UNUSED_RESULT;

int file_exists (const char *filepath) WARN_UNUSED_RESULT;
int file_append (const char *filepath, const char *data) WARN_UNUSED_RESULT;
char *file_read_content (const char *filepath) WARN_UNUSED_RESULT;


#endif /* run once */
