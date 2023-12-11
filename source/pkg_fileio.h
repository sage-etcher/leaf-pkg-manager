/* run once */
#pragma once
#ifndef __PKG_FILEIO_HEADER__
#define __PKG_FILEIO_HEADER__

#include <stdio.h>


int file_exists (const char *filepath);
char *file_read_content (const char *filepath);

#endif /* run once */
