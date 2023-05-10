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
	int num = line_number;

	temp = malloc(sizeof(stack_t));
	if (!temp)
	{
		fprintf(stderr, "%s", "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	if (!*stack)
	{
		temp->n = num;
		temp->prev = NULL;
		temp->next = NULL;
		*stack = temp;
	}
	else
	{
		temp->n = num;
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
	stack_t *temp = NULL;

	(void)line_number;
	if (*stack)
	{
		temp = *stack;
		while (temp != NULL)
		{
			printf("%d\n", temp->n);
			temp = temp->next;
		}
	}
}

/**
 * _digit_checker - checks digit by digit if there are any leters in the number
 * @number: imput number
 * Return: null if fail
*/

char *_digit_checker(char *number)
{
	int counter = 0;

	while (number[counter])
	{
		strtok(number, " \n");
		if (isdigit(number[counter]) == 0 && number[counter] != '-')
			return (NULL);
		counter++;
	}

	return (number);
}
