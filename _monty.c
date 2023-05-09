#include "monty.h"

/**
 * main - main function for monty
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: always 0
 */

int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL, *_opcode = NULL, *strtoker = NULL, *dup_line = NULL;
	size_t len = 0;
	stack_t *stack = NULL;
	void (*f)(stack_t **stack, unsigned int line_number);
	int line_counter = 1;

	if (argc != 2)
	{	fprintf(stderr, "%s", "USAGE: monty file\n");
		exit(EXIT_FAILURE); }

	stack = NULL;

	file = fopen(argv[1], "r");
	if (!file)
	{	fprintf(stderr, "%s%s%c", "Error: Can't open file ", argv[1], '\n');
		exit(EXIT_FAILURE); }

	while (getline(&line, &len, file) != -1)
	{
		dup_line = strdup(line);
		strtoker = strtok(dup_line, " /t/n$");
		if (strcmp(line, "\n") == 0)
			continue;
		_opcode = strdup(strtoker);
		strtoker = strtok(NULL, " /t/n$");
		f = get_function(strtoker, _opcode, line_counter);
		if (strtoker)
			f(&stack, atoi(strtoker));
		else
			f(&stack, 0);
		free(_opcode);
		free(dup_line);
		line_counter++;
	}
	free(line);
	fclose(file);
	free_list(stack);
	return (0);
}

/**
 * get_function - Function for getting the apropiate function
 * @number: line read from the file
 * @_opcode: its the opcode
 * @stack: head node
 * @line_number: number
 * Return: returns a function
 */

void (*get_function(char *number, char *_opcode, int line_count))(
	stack_t **stack, unsigned int line_number)
{
	int count = 0;
	instruction_t operators[] = {
		{"push", _push},
		{"pall", _pall},
		{NULL, NULL}
	};

	while (operators[count].opcode != NULL)
	{
		if (strcmp(operators[count].opcode, _opcode) == 0)
		{
			if (number && strcmp(_opcode, "push") == 0)
			{
				if ((!atoi(number) && number[0] - '0' != 0))
				{
					fprintf(stderr, "%s%d%s", "L", line_count, ": usage: push integer\n");
					exit(EXIT_FAILURE);
				}
			}
			return (operators[count].f);
		}
		count++;
	}
	fprintf(stderr, "%s%d%s", "L", line_count, ": unknown instruction <opcode>");
	exit(EXIT_FAILURE);
}
