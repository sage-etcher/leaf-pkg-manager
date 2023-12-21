/* 
 * This source file is a part of the Leaf Package Manager.
 *
 * /source/config.h
 * Contains prototypes and includes for code defined in '/source/config.c'.
 *
 */

/* 
 * Copyright 2023 Sage I. Hendricks
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
