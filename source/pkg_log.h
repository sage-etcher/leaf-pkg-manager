/* run once */
#pragma once
#ifndef __PKG_LOG_HEADER__
#define __PKG_LOG_HEADER__

#include <stdio.h>

#include "pkg_fileio.h"
#include "pkg_globals.h"


/* globals */
typedef const char * err_msg;

extern err_msg WARNING_CANNOT_LOG_TO_FILE;
extern err_msg ERROR_NO_CONFIG_FILE;
extern err_msg ERROR_PARSING_TOML;


/* function prototypes */
int  log_to_file (const char *log_file, const char *msg);
void log_to_term (FILE *stream, const char *msg);
void log_message (const char *msg);


#endif /* run once */
