/* run once */
#pragma once
#ifndef __PKG_GLOBALS_HEADER__
#define __PKG_GLOBALS_HEADER__

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

#endif /* run once */
