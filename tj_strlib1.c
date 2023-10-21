#include "main.h"

/**
 * tj_strcat - func to concatenate two strings
 * @destination: pointer to dest str.
 * @sc: pointer to source str.
 * Return: the destination.
 */
char *tj_strcat(char *destination, const char *sc)
{
	int i;
	int j;

	for (i = 0; destination[i] != '\0'; i++)
		;

	for (j = 0; sc[j] != '\0'; j++)
	{
		destination[i] = sc[j];
		i++;
	}

	destination[i] = '\0';
	return (destination);
}
/**
 * *tj_strcpy - Copies string .
 * @dest_str: pointer to the dest str.
 * @src_str: pointer to the source str
 * Return: destination str.
 */
char *tj_strcpy(char *dest_str, char *src_str)
{

	size_t i;

	for (i = 0; src_str[i] != '\0'; i++)
	{
		dest_str[i] = src_str[i];
	}
	dest_str[i] = '\0';

	return (dest_str);
}
/**
 * tj_strcmp - a function that compares two strings.
 * @s1: first str to be compared
 * @s2: second str to be compared
 * Return: zero.
 */
int tj_strcmp(char *s1, char *s2)
{
	int k;

	while (s1[k] && s1[k] == s2[k])
	{
		k++;
		if (s1[k] > s2[k])
			return (1);
		if (s1[k] < s2[k])
			return (-1);
	}

	return (0);
}
/**
 * tj_strchr - locates a char in a string,
 * @s: input string.
 * @ch: char to be located.
 * Return:  pointer to the first occurrence of the character c.
 */
char *tj_strchr(char *s, char ch)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == ch)
			return (s + i);
	if (*(s + i) == ch)
		return (s + i);
	return ('\0');
}
/**
 * tj_strspn - return the length of a  substring.
 * @str: beginnig.
 * @accept: accepted bytes.
 * Return: returns the  accepted bytes.
 */
int tj_strspn(char *str, char *accept)
{
	int i, j, bool;

	for (i = 0; *(str + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(str + i) == *(accept + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}
