#include "main.h"

/**
 * our_strstr - searches for a substring within a string
 * @sand: a pointer containing bunch of strings
 * @pins: a pointer holding the substring
 * Return: string or NULL
*/

char *our_strstr(const char *sand, const char *pins)
{
	char *pin_found;

	pin_found = (char *)sand;

	if (*pins == '\0')
	{
		return (pin_found);
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
			return (pin_found);
		}
		sand++;
	}

	return (NULL);
}


/**
 * our_strcspn - check if two strings contains matched substrings
 * @str1: first string
 * @str2: second string
 * Return: If no match is found, return the length of the entire string.
*/
size_t our_strcspn(const char *str1, const char *str2)
{
	const char *s1;
	const char *s2;

	for (s1 = str1; *s1; s1++)
	{
		for (s2 = str2; *s2; s2++)
		{
			if (*s1 == *s2)
			{
				return (s1 - str1);
			}
		}
	}
	return (s1 - str2);
}

/**
 * our_strcmp - compares two strings
 * @str1: first string
 * @str2: second string
 * Return: compared strings
 */
int our_strcmp(const char *str1, const char *str2)
{
	int cmp = *str1 - *str2;

	while (*str1 && *str2)
	{
		if (*str1 != *str2)
		{
			return (cmp);
		}

		str1++;
		str2++;
	}

	return (cmp);
}

