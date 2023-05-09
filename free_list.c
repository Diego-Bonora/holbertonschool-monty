#include "monty.h"

/**
 * free_list - frees a double linked list
 * @head: input node
 * Return: Nothing
 */

void free_list(stack_t *head)
{
	stack_t *temp;

	temp = head;
	while (head != NULL)
	{
		head = head->next;
		free(temp);
		temp = head;
	}
}
