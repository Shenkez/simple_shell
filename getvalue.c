#include "main.h"

char *get_value(envstruct *head, char *key)
{
  envstruct *curr = head;

  if (head == NULL || key == NULL)
    {
      return (NULL);
    }

  while (curr != NULL)
    {
      if (strcmp(curr->key, key) == 0)
	{
	  return (curr->value);
	}
      curr = curr->next;
    }

  return (NULL);
}
