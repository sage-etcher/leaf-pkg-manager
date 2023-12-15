/* run once */
#pragma once
#ifndef __PKG_GLOBALS_HEADER__
#define __PKG_GLOBALS_HEADER__

#include <malloc.h>

#if DEBUG == 1
#define UNUSED_RESULT __attribute__((unused-result))
#else /* DEBUG == 1 */
#define UNUSED_RESULT
#endif /* DEBUG == 1 */


/* config file */
extern const char *XDG_CONFIG_FILE;
extern const char *HOME_CONFIG_FILE;
extern const char *GLOBAL_CONFIG_FILE;
extern char *g_config_file;

/* TOML keys/tables */
extern const char *CONFIG_TABLE_GENERAL;
extern const char *CONFIG_KEY_DBFILE;
extern const char *CONFIG_KEY_LOCALPKGPATH;
extern const char *CONFIG_KEY_INSTALLPREFIX;
extern const char *CONFIG_KEY_EXTRACTPATH;
extern const char *CONFIG_KEY_LOGFILE;

/* runtime config variables */
extern char *g_config_database_file;
extern char *g_config_local_package_path;
extern char *g_config_install_prefix;
extern char *g_config_extract_path;
extern char *g_config_log_file;

/* console parameter variables/flags */
typedef enum {
    MODE_INSTALL,
    MODE_UNINSTALL,
    MODE_CREATE,
    MODE_DELETE,
    MODE_ALIAS,
    MODE_REMOVE_ALIAS,
    MODE_LIST
} mode;

extern mode   g_run_mode; 
extern int    g_console_config_flag; 
extern char  *g_console_config_filename;
extern int    g_verbose_flag; 
extern int    g_help_flag; 
extern int    g_version_flag; 
extern char **g_arguments;
extern size_t g_arguments_len;


/* function prototypes */
void global_cleanup (void);


#endif /* run once */
