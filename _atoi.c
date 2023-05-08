#include "main.h"
/**
 * _atoi - atoi
 * @s: string input
 * Return: numbers
*/

int _atoi(char *s)
{
	int num = 0;
	int sign = 1;
	int len = 0;
	int lens;
	int top = 0;

	for (lens = 0; s[lens]; lens++)
	{
		if (s[lens] >= 48 && s[lens] <= 57)
			top = 1;
		if (s[lens] == '+' && top != 1)
			sign *= 1;
		else if (s[lens] == '-' && top != 1)
			sign *= -1;
	}
	top = 0;
	while (top != 1)
	{
		if (s[len] >= 48 && s[len] <= 57)
		{
			num = num * 10;
			if (sign == 1)
				num += s[len] - '0';
			else if (sign == -1)
				num -= s[len] - '0';
			top = 2;
		}
		if (top == 2 && (s[len] < 48 && s[len > 57]))
			top = 1;

		if (len == lens)
			top = 1;
		len++;
	}
	return (num);
}
