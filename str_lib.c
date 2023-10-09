#include "main.h"

void our_strcpy(char *_to, const char *_from)
{
	/*Copy characters from src to dest until a null terminator is encountered*/
	while (*_from != '\0')
	{
		*_to = *_from;
		_to++;
		_from++;
	}
	/*Null-terminate the destination string*/
	*_to = '\0';
}

/**
 * our_strdup - duplicates string along their memory size
 * @str: the string to be dublicated
 *
 * Return: string or NULL
 */
char *our_strdup(char *string)
{
	/*int str_len;*/
	char *new_str;

	/*str_len = our_strlen(str) + 1;*/

	new_str = malloc(our_strlen(string) + 1 * sizeof(char));

	if (new_str == NULL)
	{
		return (NULL);
	}

	our_strcpy(new_str, string);

	return (new_str);
}

size_t our_strlen(const char *string) {
    size_t length = 0;

    while (string[length] != '\0') {
        length++;
    }

    return length;
}

/**
 * our_strstr - searches for a substring within a string
 * @sand: a pointer containing bunch of strings
 * @pins: a pointer holding the substring
 * Return: string or NULL
*/

char *our_strstr(const char *sand, const char *pins)
{
    /*Handle special cases*/
    char *pin_found;
    pin_found = (char *)sand;

    if (*pins == '\0')
    {
        return (pin_found); /* Needle is an empty string*/
    }

    while (*sand != '\0')
    {
        const char *san = sand;
        const char *pin = pins;

        while (*pin != '\0' && *san == *pin)
        {
            san++;
            pin++;
        }

        if (*pin == '\0')
        {
            return (pin_found); /*Needle found in haystack*/
        }

        sand++;
    }

    return (NULL); /*Needle not found*/
}

