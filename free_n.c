#include "main.h"

void free_list(envstruct **head) {
  while (*head != NULL) {
    envstruct *temp = *head;
    *head = (*head)->next;
    if (temp->key != NULL) {
      free(temp->key);
      temp->key = NULL;
    }
    if (temp->value != NULL) {
      free(temp->value);
      temp->value = NULL;
    }
    free(temp);
    temp = NULL;
  }
}
