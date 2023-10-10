#include "main.h"

int print_all(envstruct *head)
{
  envstruct *curr = head;

  while (curr != NULL)
    {
      printf("%s=%s\n", curr->key, curr->value);
      curr = curr->next;
    }
  return (0);
}
