#include "main.h"
/**
 * get_value - gets value of env var
 * @head: head variable
 * @key: value variable
 *
 * Return: NULL
*/

char *get_value(envstruct *head, char *key)
{
	envstruct *curr = head;

	if (head == NULL || key == NULL)
	{
		return (NULL);
	}

	while (curr != NULL)
	{
		if (our_strcmp(curr->key, key) == 0)
		{
			return (curr->value);
		}

		curr = curr->next;
	}

	return (NULL);
}
