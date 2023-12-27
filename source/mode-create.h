/* 
 * This source file is a part of the Leaf Package Manager.
 *
 * /source/mode-create.h
 * Contains prototypes and includes for code defined in '/source/mode-create.c'.
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
#ifndef __PKG_MODE_CREATE_HEADER__
#define __PKG_MODE_CREATE_HEADER__


#include "globals.h"


/* function prototypes */
int create_package (char *package_name, char *fakeroot_path);


#endif /* run once */


/* end of file */