#include "main.h"

/**
 * insert_end - putting a node at end of list
 * @head: list root
 * @key: key of list
 * @value: Value to add
 *
 * Return: Pointer to head of list
 */

envstruct *insert_end(envstruct *head, char *key, char *value)
{
  envstruct *curr = head;
  envstruct *new_node = malloc(sizeof(envstruct));

  if (new_node == NULL)
    {
      return (NULL);
    }

  new_node->key = strdup(key);
  new_node->value = strdup(value);
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
