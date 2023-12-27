/* 
 * This source file is a part of the Leaf Package Manager.
 * https://github.com/sage-etcher/leaf-pkg-manager
 *
 * /source/globals.h
 * Contains global variable definitions, and prototypes for '/source/globals.c'.
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


/* run once */
#pragma once
#ifndef __PKG_GLOBALS_HEADER__
#define __PKG_GLOBALS_HEADER__

#include <malloc.h>


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
/* mode required arguments */
#define ARGC_MIN_INSTALL   1
#define ARGC_MIN_UNINSTALL 1
#define ARGC_ABS_CREATE    2
#define ARGC_MIN_DELETE    1
#define ARGC_ABS_ALIAS     2
#define ARGC_MIN_RMALIAS   1
#define ARGC_MIN_LIST      0
#define ARGC_MAX_LIST      1
/* mode parameter indexing constants */
#define CREATE_PKGNAME_INDEX 0
#define CREATE_FAKEROOT_INDEX 1
#define ALIAS_SRC_INDEX 0
#define ALIAS_DST_INDEX 1
#define LIST_SRCH_INDEX 0
extern const char *LIST_DEFAULT_SEARCH_STRING;




extern mode   g_run_mode; 
extern int    g_console_config_flag; 
extern char  *g_console_config_filename;
extern int    g_verbose_flag; 
extern int    g_help_flag; 
extern int    g_version_flag; 
extern char **g_arguments;
extern size_t g_arguments_len;

/* error logging strings + typedef */
typedef const char * err_msg;

extern err_msg WARNING_CANNOT_LOG_TO_FILE;
extern err_msg ERROR_NO_CONFIG_FILE;
extern err_msg ERROR_PARSING_TOML;

extern const char *CONFIRM_INSTALL;
extern const char *CONFIRM_UNINSTALL;
extern const char *CONFIRM_DELETE;
extern const char *CONFIRM_RMALIAS;


/* function prototypes */
void global_cleanup (void);


#endif /* run once */
