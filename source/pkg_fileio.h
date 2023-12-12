/* run once */
#pragma once
#ifndef __PKG_FILEIO_HEADER__
#define __PKG_FILEIO_HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


int file_exists (const char *filepath);
char *file_read_content (const char *filepath);
char *expand_enviornment_variable (const char *s, int *expanded_flag);
char *expand_enviornment_variables_iterative (const char *s);

#endif /* run once */
