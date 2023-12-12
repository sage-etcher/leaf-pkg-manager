#include "pkg.h"
#include <stdio.h>
#include <stdlib.h>

#include "pkg_globals.h"
#include "pkg_config.h"


/* static-function prototypes */


/* main entry point */
int
main (int argc, char **argv)
{
    int exit_code;

    exit_code = conf_source ();
    if (exit_code != 0)
    {
        exit (-1);
    }
    

	return (EXIT_SUCCESS);
    exit (0);
}


/* functions */



