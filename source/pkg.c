/* 
 * This source file is a part of the Leaf Package Manager.
 *
 * /source/pkg.c
 * The main entry point of the program.
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


#include "pkg.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "debug.h"
#include "globals.h"
#include "conargs.h"
#include "config.h"


/* static-function prototypes */


/* main entry point */
int
main (int argc, char **argv)
{
    conarg_settings (argc, argv);   /* get console parameters */
    conf_source ();                 /* source the config file */

    /* free allocated global variables and tidy up a bit */
    global_cleanup();
    /* exit */
    return EXIT_SUCCESS;
}


/* functions */

