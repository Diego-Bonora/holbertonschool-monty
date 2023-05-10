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
	size_t len = 0;
	stack_t *stack = NULL;
	void (*f)(stack_t **stack, unsigned int line_number);
	int line_counter = 1;

	if (argc != 2)
	{	fprintf(stderr, "%s", "USAGE: monty file\n");
		exit(EXIT_FAILURE); }

	file = fopen(argv[1], "r");
	if (!file)
	{	fprintf(stderr, "%s%s%c", "Error: Can't open file ", argv[1], '\n');
		exit(EXIT_FAILURE); }

	while (getline(&line, &len, file) != -1)
	{
		strtoker = strtok(line, " \t");
		if (strcmp(strtoker, "\n") != 0)
		{	_opcode = strdup(strtoker);
			strtoker = strtok(NULL, " \t");
			f = get_function(strtoker, _opcode, line_counter);
			if (error_flag == 1)
			{	free(_opcode), free(line), fclose(file), free_list(stack);
				exit(EXIT_FAILURE); }
			if (strtoker)
				f(&stack, atoi(strtoker));
			else
				f(&stack, 0);
			if (error_flag == 1)
			{	fprintf(stderr, "%s%d%s", "L", line_counter,
				 ": can't pint, stack empty\n");
				free(_opcode), free(line), fclose(file), free_list(stack);
				exit(EXIT_FAILURE); }
			free(_opcode); }
		line_counter++; }
	free(line), fclose(file), free_list(stack);
	return (0); }

/**
 * get_function - Function for getting the apropiate function
 * @number: line read from the file
 * @_opcode: its the opcode
 * @stack: head node
 * @line_number: parameter for the function
 * Return: returns a function
 */

void (*get_function(char *number, char *_opcode, int line_count))(
	stack_t **stack, unsigned int line_number)
{
	int count = 0;
	instruction_t operators[] = {
		{"push", _push},
		{"pall", _pall},
		{"pint", _pint},
		{NULL, NULL}
	};
	strtok(_opcode, " \n");
	while (operators[count].opcode != NULL)
	{
		if (strcmp(operators[count].opcode, _opcode) == 0)
		{
			if (number && strcmp(_opcode, "push") == 0)
			{
				number = _digit_checker(number);
				if ((!number))
				{
					fprintf(stderr, "%s%d%s", "L", line_count, ": usage: push integer\n");
					error_flag = 1;
					return (NULL);
				}
			}
			return (operators[count].f);
		}
		count++;
	}
	fprintf(stderr, "%s%d%s%s%c", "L",
	 line_count, ": unknown instruction ", _opcode, '\n');
	error_flag = 1;
	return (NULL);
}

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
