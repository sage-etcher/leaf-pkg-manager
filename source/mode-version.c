/* 
 * This source file is a part of the Leaf Package Manager.
 * https://github.com/sage-etcher/leaf-pkg-manager
 *
 * /source/mode-version.c
 * Contains functions needed to print the version information
 *
 */

/* 
 * Copyright 2023-2024 Sage I. Hendricks
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


#include "mode-version.h"

#include <stdio.h>

#include "globals.h"


void
version_message (void)
{
    /* print the version message to stdout */
    puts (VERSION_MESSAGE);
    fflush (stdout);

    /* exit the function */
    return;
}


/* end of file */
