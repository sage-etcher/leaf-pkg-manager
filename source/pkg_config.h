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

#include "pkg_debug.h"
#include "pkg_globals.h"
#include "pkg_fileio.h"
#include "pkg_log.h"


/* get the most relevent config file */
const char *conf_get_file (void);

/* interpret the config file from human readable format to usable data */
int conf_interpret (const char * restrict content);

/* source the config file, getting needed configureation settings from it */
int conf_source (void);



#endif /* run once */
