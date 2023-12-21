/* 
 * This source file is a part of the Leaf Package Manager.
 *
 * /source/log.h
 * Contains prototypes and includes for code defined in '/source/log.c'.
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
#ifndef __PKG_LOG_HEADER__
#define __PKG_LOG_HEADER__

#include <stdio.h>

#include "debug.h"
#include "fileio.h"
#include "globals.h"


/* globals */
typedef const char * err_msg;

extern err_msg WARNING_CANNOT_LOG_TO_FILE;
extern err_msg ERROR_NO_CONFIG_FILE;
extern err_msg ERROR_PARSING_TOML;


/* function prototypes */
int  log_to_file (const char *log_file, const char *msg) WARN_UNUSED_RESULT;
void log_to_term (FILE *stream, const char *msg);
void log_message (const char *msg);


#endif /* run once */