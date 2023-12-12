#include "pkg_config.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

/* TOML v1.0.0 <https://github.com/cktan/tomc99.git> */
/* MIT License */
#include <toml.h>

#include "pkg_globals.h"
#include "pkg_fileio.h"


/* function prototypes */
static char *get_toml_string (toml_table_t *table, const char *key);


/* function definitions */
const char *
conf_get_file (void)
{
    const char *selected_config_file = NULL;    /* default NULL */
    char *expanded_xdg_config, *expanded_home_config, *expanded_global_config;

    /* expanded versin of config files */
    expanded_xdg_config = expand_enviornment_variables_iterative(XDG_CONFIG_FILE);
    expanded_home_config = expand_enviornment_variables_iterative(HOME_CONFIG_FILE);
    expanded_global_config = expand_enviornment_variables_iterative(GLOBAL_CONFIG_FILE);

    /* go through the if else statement, favoring the upper most file */
    /* default is defined as NULL in variable declaration */
    if (file_exists (expanded_xdg_config))
    {
        selected_config_file = XDG_CONFIG_FILE;
    }
    else if (file_exists (expanded_home_config))
    {
        selected_config_file = HOME_CONFIG_FILE;
    }
    else if (file_exists (expanded_global_config))
    {
        selected_config_file = GLOBAL_CONFIG_FILE;
    }

    /* free the expanded file paths */
    free (expanded_global_config);
    free (expanded_home_config);
    free (expanded_xdg_config);

    /* return the result */
    return selected_config_file;
}


static char *
get_toml_string (toml_table_t *table, const char *key)
{
    toml_datum_t toml_data;
    
    toml_data = toml_string_in (table, key);
    if (!toml_data.ok)
    {
        fprintf (stderr, "ERROR: connot parse TOML\n");
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
    if (!toml_config)
    {
        fprintf (stderr, "ERROR: cannot parse config file");
        exit (-1);
    }

    /* load the general table */
    toml_general_table = toml_table_in(toml_config, CONFIG_TABLE_GENERAL); 

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
        fprintf (stderr, "ERROR: missing field in config\n");
        exit (-1);
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
        fprintf (stderr, "ERROR: could not find configuration file, \"%s\"\n",
                GLOBAL_CONFIG_FILE);
        return -1;
    }

    (void)conf_interpret_toml (g_config_file);

    return 0;
}


/* end of file */
