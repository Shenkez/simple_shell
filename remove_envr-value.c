#include "main.h"

/**
 * remove_value - remove env variable
 * @head: head variable
 * @key: key variable
 *
 * Return: 0 or 1
*/
int remove_value(envstruct **head, char *key)
{
	envstruct *curr = *head;
	envstruct *prev = NULL;

	if (head == NULL || *head == NULL)
	{
		return (1);
	}

	while (curr != NULL)
	{
		int _strcmp = our_strcmp(curr->key, key);

		if (_strcmp == 0)
		{
			if (prev == NULL)
			{
				*head = curr->next;
			}
			else
			{
				prev->next = curr->next;
			}

			free(curr->key);
			free(curr->value);
			free(curr);
			return (0);
		}

		prev = curr;
		curr = curr->next;
	}

	return (1);
}
