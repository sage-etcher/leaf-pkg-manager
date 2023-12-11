#include "pkg_fileio.h"

#include <stdio.h>


int
file_exists (const char * restrict filepath)
{
	FILE *fp;

	/* try to open the file */
	fp = fopen (filepath, "r");
	/* if fopen succeeds, close the file, and return a success */ 
	if (fp != NULL)
	{
		fclose (fp);
		return (1);
	}

	/* otherwise, if the command fails, return a failures */
	return (0);
}


size_t
file_text_size (FILE * restrict fp)
{
	size_t file_pos, file_size;

	/* save the stream's position */
	file_pos = ftell (fp);

	/* goto the end of the stream and get the offset */
	fseek (fp, 0L, SEEK_END);
	file_size = ftell (fp);
	
	/* restore the stream's position */
	fseek (fp, file_pos, SEEK_SET);

	/* return size of the given stream */
	return file_size;
}

char *
file_read_content (const char * restrict filepath)
{
	FILE * restrict fp = NULL;
	char * restrict content = NULL;
	size_t content_size; 

	/* open the file */
	fp = fopen (filepath, "r");
	if (fp == NULL)
		return NULL;

	/* get size of content */
	content_size = file_text_size (fp);
	content = (char * restrict)malloc (content_size);

	/* read data from the file into content */
	(void)fgets (content, content_size, fp);

	/* close the file and exit */
	fclose (fp);
	return content;
}

/* end of file */
