#include "main.h"


/**
 * clean_up - frees the lineptr upon exit
 *
 * Return: void
 */
void clean_up(void)
{
	if (lineptr != NULL)
		free(lineptr);
}

