#include "main.h"


envstruct *insert_end(envstruct *head, char *key, char *value)
{
	envstruct *curr = head;
	envstruct *new_node = malloc(sizeof(envstruct));

	if (new_node == NULL)
	{
		return (NULL);
	}

	new_node->key = our_strdup(key);
	new_node->value = our_strdup(value);
	new_node->next = NULL;

	if (head == NULL)
	{
		return (new_node);
	}

	while (curr->next != NULL)
	{
		curr = curr->next;
	}

	curr->next = new_node;

	return (head);
}
