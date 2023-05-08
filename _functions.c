#include "monty.h"

/**
 * _push - function for pushing a number to the stack
 * @stack: head node of the stack
 * @line_number: number to add to the new node
 * Return: nothing
 */

void _push(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	temp = malloc(sizeof(stack_t));
	if (!temp)
	{
		fprintf(stderr, "%s", "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	if (!*stack)
	{
		temp->n = line_number;
		temp->prev = NULL;
		temp->next = NULL;
		*stack = temp;
	}
	else
	{
		temp->n = line_number;
		temp->prev = NULL;
		temp->next = *stack;
		(*stack)->prev = temp;
		*stack = temp;
	}
}

/**
 * _pall - function for printing all the stack
 * @stack: head node of the stack
 * @line_number: unnesesary variable
 * Return: nothing
 */

void _pall(stack_t **stack, unsigned int line_number)
{
	(void)line_number;
	if (*stack)
	{
		while (*stack != NULL)
		{
			printf("%d\n", (*stack)->n);
			*stack = (*stack)->next;
		}
	}
}
