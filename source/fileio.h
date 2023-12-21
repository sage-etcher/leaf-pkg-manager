/* 
 * This source file is a part of the Leaf Package Manager.
 *
 * /source/fileio.h
 * Contains prototypes and includes for code defined in '/source/fileio.c'.
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
