#include "pkg_globals.h"

/* config file locations */
const char *XDG_CONFIG_FILE    = "$XDG_CONFIG_HOME/pkg/config.toml";
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


