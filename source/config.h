/* run once */
#pragma once
#ifndef __PKG_CONFIG_HEADER__
#define __PKG_CONFIG_HEADER__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

/* TOML v1.0.0 <https://github.com/cktan/tomc99.git> */
/* MIT License */
#include <toml.h>

#include "debug.h"
#include "globals.h"
#include "fileio.h"
#include "log.h"


/* get the most relevent config file */
const char *conf_get_file (void) WARN_UNUSED_RESULT;

/* interpret the config file from human readable format to usable data */
int conf_interpret (const char * restrict content) WARN_UNUSED_RESULT;

/* source the config file, getting needed configureation settings from it */
void conf_source (void);



#endif /* run once */
