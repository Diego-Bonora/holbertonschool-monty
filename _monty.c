#include "monty.h"

int error_flag = 0;

/**
 * main - main function for monty
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: always 0
 */

int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL, *_opcode = NULL, *strtoker = NULL;
	size_t len = 0, line_counter = 1;
	stack_t *stack = NULL;
	void (*f)(stack_t **stack, unsigned int line_number);

	if (argc != 2)
	{	fprintf(stderr, "%s", "USAGE: monty file\n");
		exit(EXIT_FAILURE); }
	file = fopen(argv[1], "r");
	if (!file)
	{	fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE); }
	while (getline(&line, &len, file) != -1)
	{	strtoker = strtok(line, " \t");
		if (strcmp(strtoker, "\n") != 0)
		{	_opcode = strdup(strtoker);
			strtoker = strtok(NULL, " \t");
			f = get_function(strtoker, _opcode, line_counter, &error_flag);
			if (error_flag == 1)
			{	free(_opcode), free(line), fclose(file), free_list(stack);
				exit(EXIT_FAILURE); }
			if (strtoker)
				f(&stack, atoi(strtoker));
			else
				f(&stack, 0);
			if (error_flag == 1)
			{	fprintf(stderr, "L%ld: can't pint, stack empty\n", line_counter); }
			else if (error_flag == 2)
			{	fprintf(stderr, "L%ld: can't pop an empty stack\n", line_counter); }
			else if (error_flag == 3)
			{	fprintf(stderr, "L%ld: can't swap, stack too short\n", line_counter); }
			else if (error_flag == 4)
			{	fprintf(stderr, "L%ld: can't add, stack too short\n", line_counter); }
			if (error_flag != 0)
			{	free(_opcode), free(line), fclose(file), free_list(stack);
				exit(EXIT_FAILURE); }
			free(_opcode); }
		line_counter++; }
	free(line), fclose(file), free_list(stack);
	return (0); }

/**
 * _pint - prints the head node of the stack
 * @stack: head node
 * @line_number: parameter for the function
 * Return: nothing
*/

void _pint(stack_t **stack, unsigned int line_number)
{
	(void)line_number;
	if (*stack)
	{
		printf("%d\n", (*stack)->n);
	}
	else
	{
		error_flag = 1;
	}
}

/**
 * _pop - removes the top element of the stack
 * @stack: head node
 * @line_number: parameter for the function
 * Return: nothing
*/

void _pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	(void)line_number;
	if (*stack)
	{
		if ((*stack)->next)
		{
			temp = *stack;
			(*stack) = (*stack)->next;
			(*stack)->prev = NULL;
			free(temp);
		}
		else
		{
			free(*stack);
			*stack = NULL;
		}
	}
	else
	{
		error_flag = 2;
	}
}

/**
 * _swap - swaps the top elements of the stack
 * @stack: head node
 * @line_number: parameter for the function
 * Return: nothing
*/

void _swap(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;
	unsigned int num_changer = 0;

	(void)line_number;
	if (*stack && (*stack)->next)
	{
		temp = (*stack)->next;
		num_changer = (*stack)->n;
		(*stack)->n = temp->n;
		temp->n = num_changer;
	}
	else
	{
		error_flag = 3;
	}
}

/**
 * _add - adds the top elements of the stack
 * @stack: head node of the stack
 * @line_number: unnesesary variable
 * Return: nothing
 */

void _add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	(void)line_number;
	if (*stack && (*stack)->next)
	{
		temp = *stack;
		*stack = (*stack)->next;
		(*stack)->n = temp->n + (*stack)->n;
		(*stack)->prev = NULL;
		free(temp);
	}
	else
	{
		error_flag = 4;
	}
}
