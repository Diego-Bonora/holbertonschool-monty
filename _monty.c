#include "main.h"

/**
 * main - main function for monty
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: always 0
 */

int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL, *_opcode = NULL;
	size_t len = 0;
	stack_t *stack = NULL;
	void (*f)(stack_t **stack, unsigned int line_number);

	if (argc != 2)
	{
		fprintf(stderr, "%s", "USAGE: monty file");
		exit(EXIT_FAILURE);
	}

	stack = malloc(sizeof(stack_t));
	if (!stack)
	{
		fprintf(stderr, "%s", "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	stack = NULL;

	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "%s%s%c", "Error: Can't open file ", argv[1], '\n');
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, file) != -1)
	{
		_opcode = _get_opcode(line);
		f = get_function(line, _opcode);
		f(&stack, _atoi(line));
		free(_opcode);
	}
	fclose(file);
	return (0);
}

/**
 * _get_opcode - function for getting the opcode
 * @line: line read from the file
 * Return: returns the opcode found in the line
 */

char *_get_opcode(char *line)
{
	int count = 0, total = 0;
	char *r_opcode = NULL;

	while (line[count] != ' ' && line[count] != '$')
		count++;
	total = count;
	count = 0;
	r_opcode = malloc(total);
	if (!r_opcode)
	{
		fprintf(stderr, "%s", "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	for (count = 0; count < total; count++)
	{
		r_opcode[count] = line[count];
	}
	return (r_opcode);
}

/**
 * get_function - Function for getting the apropiate function
 * @line: line read from the file
 * @stack: head node
 * @line_number: number
 * Return: returns a function
 */

void (*get_function(char *line, char *_opcode))(
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
			if (!_atoi(line) && strcmp(_opcode, "push") == 0)
			{
				fprintf(stderr, "%s%d%s", "L", 50, ": usage: push integer\n");
				exit(EXIT_FAILURE);
			}
			return (operators[count].f);
		}
		count++;
	}
	fprintf(stderr, "%s%d%s", "L", 91, ": unknown instruction <opcode>");
	exit(EXIT_FAILURE);
}
