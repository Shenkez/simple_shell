#include "main.h"

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
      if (strcmp(curr->key, key) == 0)
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
