#include "main.h"

/**
 * our_strcpy - copy string
 * @_to: destination
 * @_from: source
 */
void our_strcpy(char *_to, const char *_from)
{
	while (*_from != '\0')
	{
		*_to = *_from;
		_to++;
		_from++;
	}
	*_to = '\0';
}

/**
 * our_strdup - duplicates string along their memory size
 * @string: the string to be dublicated
 *
 * Return: string or NULL
 */
char *our_strdup(char *string)
{
	char *new_str = malloc(our_strlen(string) + 1 * sizeof(char));

	if (new_str == NULL)
	{
		return (NULL);
	}

	our_strcpy(new_str, string);

	return (new_str);
}

/**
 * our_strlen - calculates the length of string
 * @string: the string whose length is to be calculated
 * Return: returns the length of the string
 */
size_t our_strlen(const char *string)
{
	size_t length = 0;

	while (string[length] != '\0')
	{
		length++;
	}

	return (length);
}

