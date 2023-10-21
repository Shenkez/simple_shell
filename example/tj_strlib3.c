#include "main.h"

/**
 * str_rev - string to be reversed.
 * @str: input string.
 * Return: nothing.
 */
void str_rev(char *str)
{
	int count = 0, j, k;
	char *string, temp;

	while (count >= 0)
	{
		if (str[count] == '\0')
			break;
		count++;
	}
	string = str;

	for (j = 0; j < (count - 1); j++)
	{
		for (k = j + 1; k > 0; k--)
		{
			temp = *(string + k);
			*(string + k) = *(string + (k - 1));
			*(string + (k - 1)) = temp;
		}
	}
}
