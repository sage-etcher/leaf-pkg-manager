#include "pkg_config.h"

#include <complex.h>
#include <stdio.h>
#include <malloc.h>

/* TOML v1.0.0 <https://github.com/cktan/tomc99.git> */
/* MIT License */
#include <toml.h>

#include "pkg_globals.h"
#include "pkg_fileio.h"


const char *
conf_get_file (void)
{
	/* favor $XDG_CONFIG_HOME config file */
	if (file_exists (XDG_CONFIG_FILE))
		return (XDG_CONFIG_FILE);

	/* if no user config file is found, use the global one */
	if (file_exists (GLOBAL_CONFIG_FILE))
		return (GLOBAL_CONFIG_FILE);

	/* if neither file exists, there is a serious issue */
	return NULL;
}


int
conf_interpret_toml (const char * restrict filepath)
{
	FILE * restrict fp;
	toml_table_t *toml_config, *toml_general_table;
	toml_datum_t toml_data;
	char error_buff[200];

	/* open the file */
	fp = fopen (filepath, "r");

	/* load the file as TOML v1.0.0 */
	toml_config = toml_parse_file (fp, error_buff, sizeof (error_buff));
	if (!toml_config)
	{
		fprintf (stderr, "ERROR: cannot parse config file");
		return -1;
	}


	/* load the general table */
	toml_general_table = toml_table_in(toml_config, CONFIG_TABLE_GENERAL); 


	/* get the database file path from the config file */
	toml_data = toml_string_in (toml_general_table, CONFIG_KEY_DBFILE);
	if (!toml_data.ok)
	{
		fprintf (stderr, "cannot parse \'%s\' in config file", CONFIG_KEY_DBFILE);
		return -1;
	}
	g_config_database_file = str_clone (toml_data.u.s);
	free (toml_data.u.s);

	/* get the local package path from the config file */
	toml_data = toml_string_in (toml_general_table, CONFIG_KEY_LOCALPKGPATH);

	/* get the install prefix from the config file */
	toml_data = toml_string_in (toml_general_table, CONFIG_KEY_INSTALLPREFIX);

	/* get the extract path from the config file */
	toml_data = toml_string_in (toml_general_table, CONFIG_KEY_EXTRACTPATH);

	/* get the log file path from the config file */
	toml_data = toml_string_in (toml_general_table, CONFIG_KEY_LOGFILE);



	toml_free (toml_config);

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
