#include "main.h"

/**
 * tj_strdup - a func that duplicates a string.
 * @str1: a pointer to the first string.
 * Return: the duplicated string str2.
 */
char *tj_strdup(const char *str1)
{
	char *str2;
	size_t len;

	len = tj_strlen(str1);
	str2 = malloc(sizeof(char) * (len + 1));
	if (str2 == NULL)
		return (NULL);
	_memcpy(str2, str1, len + 1);
	return (str2);
}

/**
 * tj_strlen - calculates the lenght of a string.
 * @str: a pointer to the str whose length is to be calculated.
 * Return: returns the strlen.
 */
int tj_strlen(const char *str)
{
	int len;

	for (len = 0; str[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * tj_cmp_chars - it compares chars of strings.
 * @strn: the input str.
 * @del: delimiter.
 *
 * Return: returns 1 if equal, 0 if not.
 */
int tj_cmp_chars(char strn[], const char *del)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; strn[i]; i++)
	{
		for (j = 0; del[j]; j++)
		{
			if (strn[i] == del[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * tj_strtok - seperate strings based on a delimiter.
 * @strn: string to be tokenize.
 * @del: the delimiter.
 *
 * Return: returns splited str.
 */
char *tj_strtok(char strn[], const char *del)
{
	char *s_start;
	static char *splitt, *s_end;
	unsigned int i, bool;

	if (strn != NULL)
	{
		if (tj_cmp_chars(strn, del))
			return (NULL);
		splitt = strn;
		i = tj_strlen(strn);
		s_end = &strn[i];
	}
	s_start = splitt;
	if (s_start == s_end)
		return (NULL);

	for (bool = 0; *splitt; splitt++)
	{
		if (splitt != s_start)
			if (*splitt && *(splitt - 1) == '\0')
				break;
		for (i = 0; del[i]; i++)
		{
			if (*splitt == del[i])
			{
				*splitt = '\0';
				if (splitt == s_start)
					s_start++;
				break;
			}
		}
		if (bool == 0 && *splitt)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (s_start);
}

/**
 * tj_isdigit - checks for a digit.
 *
 * @str: string to be checked.
 * Return: returns 1 if string is a number. else 0 .
 */
int tj_isdigit(const char *str)
{
	unsigned int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
	}
	return (1);
}
