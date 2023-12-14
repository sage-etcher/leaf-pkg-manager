#include "pkg.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "pkg_debug.h"
#include "pkg_globals.h"
#include "pkg_conargs.h"
#include "pkg_config.h"


/* static-function prototypes */
static void print_config (void);


/* main entry point */
int
main (int argc, char **argv)
{
    (void)conarg_settings (argc, argv);   /* get console parameters */
    (void)conf_source ();                 /* source the config file */

    /*print_config ();*/
    

    /* free allocated global variables and tidy up a bit */
    global_cleanup();
    /* exit */
    return EXIT_SUCCESS;
}


/* functions */
static void
print_config (void)
{
    (void)printf ("%s\n", g_config_file);
    (void)printf ("database file  = %s\n", g_config_database_file);
    (void)printf ("package path   = %s\n", g_config_local_package_path);
    (void)printf ("install prefix = %s\n", g_config_install_prefix);
    (void)printf ("extract path   = %s\n", g_config_extract_path);
    (void)printf ("log file       = %s\n", g_config_log_file);

    return;
}


