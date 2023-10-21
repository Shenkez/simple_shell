#include "main.h"

/**
 * checks_env - func that checks if the typed
 * variable is an env variable
 *
 * @h: head pointer of linked list
 * @in_str: the input string
 * @data: var of data structure
 * Return: none
 */
void checks_env(var_list **h, char *in_str, runtime *data)
{
	int r, ch, j, val;
	char **tj_envr;

	tj_envr = data->_environ;
	for (r = 0; tj_envr[r]; r++)
	{
		for (j = 1, ch = 0; tj_envr[r][ch]; ch++)
		{
			if (tj_envr[r][ch] == '=')
			{
				val = tj_strlen(tj_envr[r] + ch + 1);
				add_rvar_node(h, j, tj_envr[r] + ch + 1, val);
				return;
			}

			if (in_str[j] == tj_envr[r][ch])
				j++;
			else
				break;
		}
	}

	for (j = 0; in_str[j]; j++)
	{
		if (in_str[j] == ' ' || in_str[j] == '\t' || in_str[j] == ';' || in_str[j] == '\n')
			break;
	}

	add_rvar_node(h, j, NULL, 0);
}

/**
 * _check_vars - checks if the typed variable is $$ or $?
 *
 * @h: head pointerof the linked list
 * @in_str: the inp string
 * @s: the last status of the Shell
 * @data: data structure
 * Return: none
 */
int _check_vars(var_list **h, char *in_str, char *s, runtime *data)
{
	int i, lst, lpd;

	lst = tj_strlen(s);
	lpd = tj_strlen(data->pid);

	for (i = 0; in_str[i]; i++)
	{
		if (in_str[i] == '$')
		{
			if (in_str[i + 1] == '?')
				add_rvar_node(h, 2, s, lst), i++;
			else if (in_str[i + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), i++;
			else if (in_str[i + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in_str[i + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in_str[i + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in_str[i + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in_str[i + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				checks_env(h, in_str + i, data);
		}
	}

	return (i);
}

/**
 * rep_input - changes string into variables
 *
 * @head: poiter head of the linked list
 * @inp: input str to be replaced
 * @new_inp: string replaced
 * @n_len: new len of str
 * Return: the replaced string
 */
char *rep_input(var_list **head, char *inp, char *new_inp, int n_len)
{
	var_list *index;
	int i, j, k;

	index = *head;
	for (j = i = 0; i < n_len; i++)
	{
		if (inp[j] == '$')
		{
			if (!(index->len_var) && !(index->len_val))
			{
				new_inp[i] = inp[j];
				j++;
			}
			else if (index->len_var && !(index->len_val))
			{
				for (k = 0; k < index->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < index->len_val; k++)
				{
					new_inp[i] = index->val[k];
					i++;
				}
				j += (index->len_var);
				i--;
			}
			index = index->next;
		}
		else
		{
			new_inp[i] = inp[j];
			j++;
		}
	}

	return (new_inp);
}

/**
 * rep_var - calls functions to replace string into vars
 *
 * @input: input string
 * @datash: data structure
 * Return: replaced string
 */
char *repl_var(char *inp, runtime *datash)
{
	var_list *head, *index;
	char *stat, *new_inp;
	int len1, len2;

	stat = aux_itoa(datash->status);
	head = NULL;

	len1 = _check_vars(&head, inp, stat, datash);

	if (head == NULL)
	{
		free(stat);
		return (inp);
	}

	index = head;
	len2 = 0;

	while (index != NULL)
	{
		len2 += (index->len_val - index->len_var);
		index = index->next;
	}

	len2 += len1;

	new_inp = malloc(sizeof(char) * (len2 + 1));
	new_inp[len2] = '\0';

	new_inp = rep_input(&head, inp, new_inp, len2);

	free(inp);
	free(stat);
	free_rvar_list(&head);

	return (new_inp);
}
