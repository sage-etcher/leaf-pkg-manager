#include "pkg.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "pkg_debug.h"
#include "pkg_globals.h"
#include "pkg_conargs.h"
#include "pkg_config.h"


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

