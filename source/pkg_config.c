#include "pkg_config.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

/* TOML v1.0.0 <https://github.com/cktan/tomc99.git> */
/* MIT License */
#include <toml.h>

#include "pkg_debug.h"
#include "pkg_globals.h"
#include "pkg_fileio.h"
#include "pkg_log.h"


/* function prototypes */
static char *get_toml_string (toml_table_t *table, const char *key);


/* function definitions */
const char *
conf_get_file (void)
{
    char *expanded_xdg, *expanded_home, *expanded_global;

    /* use the expanded for of XDG_CONFIG_FILE if the file exists */
    expanded_xdg = expand_enviornment_variables_iterative(XDG_CONFIG_FILE);
    if (file_exists (expanded_xdg))
    {
        return expanded_xdg;
    }
    TRACE_FREE (expanded_xdg);
   

    /* use the expanded for of XDG_CONFIG_FILE if the file exists */
    expanded_home = expand_enviornment_variables_iterative(HOME_CONFIG_FILE);
    if (file_exists (expanded_home))
    {
        return expanded_home;
    }
    TRACE_FREE (expanded_home);
    
    /* use the expanded for of XDG_CONFIG_FILE if the file exists */
    expanded_global = expand_enviornment_variables_iterative(GLOBAL_CONFIG_FILE);
    if (file_exists (expanded_global))
    {
        return expanded_global;
    }
    TRACE_FREE (expanded_global);


    /* if no config file exists/is found, return NULL ptr */
    return NULL;
}


static char *
get_toml_string (toml_table_t *table, const char *key)
{
    toml_datum_t toml_data;

    toml_data = toml_string_in (table, key);

    if (!toml_data.ok)
    {
        return NULL;
    }
  
    return toml_data.u.s;
}


int
conf_interpret_toml (const char * restrict filepath)
{
    FILE * restrict fp;
    toml_table_t *toml_config, *toml_general_table;
    char error_buff[200];

    /* open the file */
    fp = fopen (filepath, "r");

    /* load the file as TOML v1.0.0 */
    toml_config = toml_parse_file (fp, error_buff, sizeof (error_buff));
    (void)fclose (fp);

    if (!toml_config)
    {
        return -1;
    }

    /* load the general table */
    toml_general_table = toml_table_in(toml_config, CONFIG_TABLE_GENERAL); 
    if (toml_general_table == NULL)
    {
        return -1;
    }

    /* get the database file path from the config file */
    g_config_database_file = get_toml_string (toml_general_table, CONFIG_KEY_DBFILE); 
    g_config_local_package_path = get_toml_string (toml_general_table, CONFIG_KEY_LOCALPKGPATH);
    g_config_install_prefix = get_toml_string (toml_general_table, CONFIG_KEY_INSTALLPREFIX);
    g_config_extract_path = get_toml_string (toml_general_table, CONFIG_KEY_EXTRACTPATH);
    g_config_log_file = get_toml_string (toml_general_table, CONFIG_KEY_LOGFILE);

    /* free the toml table */
    toml_free (toml_config);
    
    /* make sure that the required variables are set in the config file */
    if ((g_config_database_file == NULL) ||
        (g_config_local_package_path == NULL) ||
        (g_config_install_prefix == NULL) ||
        (g_config_extract_path == NULL) ||
        (g_config_log_file == NULL))
    {
        return -1;
    }

    return 0;   
}


int
conf_source (void)
{
    /* get the configuration file to use */
    g_config_file = (char *)conf_get_file ();
    if (g_config_file == NULL)
    {
        log_to_term (stderr, ERROR_NO_CONFIG_FILE);
        exit (-1);
    }

    /* try to parse the config file, throw error if an issue occurs */
    if (conf_interpret_toml (g_config_file) != 0)
    {
        log_to_term (stderr, ERROR_PARSING_TOML);
        exit (-1);
    }

    return 0;
}


/* end of file */
