#include "pkg_globals.h"

#include <malloc.h>

#include "pkg_debug.h"

/* config file locations */
const char *XDG_CONFIG_FILE    = "${XDG_CONFIG_HOME}/pkg/config.toml";
const char *HOME_CONFIG_FILE   = "${HOME}/.pkg.toml";
const char *GLOBAL_CONFIG_FILE = "/etc/pkg/config.toml";
/* selected config file to use (points to one the above) */
char *g_config_file;

/* TOML keys/tables */
const char *CONFIG_TABLE_GENERAL     = "general";
const char *CONFIG_KEY_DBFILE        = "database_file";
const char *CONFIG_KEY_LOCALPKGPATH  = "local_package_path";
const char *CONFIG_KEY_INSTALLPREFIX = "install_prefix";
const char *CONFIG_KEY_EXTRACTPATH   = "extract_path";
const char *CONFIG_KEY_LOGFILE       = "log_file";
/* where the data gets stored */
char *g_config_database_file;
char *g_config_local_package_path;
char *g_config_install_prefix;
char *g_config_extract_path;
char *g_config_log_file;


/* function prototypes */
static void free_config (void);


/* functions */
void
global_cleanup (void)
{
    /* clean up config settings */
    free_config ();
    TRACE_FREE (g_config_file);
}
    

static void 
free_config (void)
{
    TRACE_FREE (g_config_database_file);
    TRACE_FREE (g_config_local_package_path);
    TRACE_FREE (g_config_install_prefix);
    TRACE_FREE (g_config_extract_path);
    TRACE_FREE (g_config_log_file);

    return;
}


/* end of file */
