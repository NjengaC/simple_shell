#include "shell.h"
/**
 * handle_replace - handles the variable replacer $
 * @command: commandline as typed
 * Return: the replacement value
 */

char *handle_replace(char *command)
{
	char *dollar_pos;
	char *env_var;
	char *replaced;
	char *remaining = NULL;
	char *var_val;
	int var_length;
	char *var_name, *exit_status_str;
	int new_length, exit_s = 0;
	pid_t pid;
	char *pid_str, *new_str;
	size_t before, after;

	remaining = strdup(command);
	while ((dollar_pos = strchr(remaining, '$')) != NULL)
	{
		if (*(dollar_pos + 1) == '$')
		{
			pid = getpid();
			pid_str = itoa(pid);
			before = dollar_pos - remaining;
			after = strlen(dollar_pos + 2);
			new_str = (char *)malloc(before + strlen(pid_str) + after + 1);
			strncpy(new_str, remaining, before);
			strcat(new_str, pid_str);
			strcat(new_str, dollar_pos + 2);
			free(remaining);
			free(pid_str);
			remaining = new_str;
		}
		else if (*(dollar_pos + 1) == '?')
		{
			if (WIFEXITED(exit_s))
			{
				exit_s = WEXITSTATUS(exit_s);
			}
			
			exit_status_str = itoa(exit_s);
			before = dollar_pos - remaining;
			after = strlen(dollar_pos + 2); 

			new_str = (char *)malloc(before + strlen(exit_status_str) + after + 1);
			strncpy(new_str, remaining, before);
			strcat(new_str, exit_status_str);
			strcat(new_str, dollar_pos + 2);

			free(remaining);
			free(exit_status_str);
			remaining = new_str;
		}
		else
		{
		var_length = 0;
		env_var = dollar_pos + 1;
		while (env_var[var_length] && isalnum(env_var[var_length]))
		{
			var_length++;
		}
		var_name = malloc(sizeof(char) * (var_length + 1));

		strncpy(var_name, env_var, var_length);
		var_name[var_length] = '\0';
		var_val = getenv(var_name);
		if (var_val)
		{

			new_length = dollar_pos - remaining + strlen(var_val);
			replaced = (char *)malloc(new_length + 1);
			strncpy(replaced, remaining, dollar_pos - remaining);
			strcat(replaced, var_val);
			strcat(replaced, dollar_pos + var_length + 1);
			free(remaining);
			remaining = replaced;
		}
		else
		{

			remaining = dollar_pos + 1;
		}
		}
	}
	return(remaining);
}



char *itoa(int num)
{
	char *str;
	int temp, i;
	int numDigits = 0;

	temp = num;
	while (temp != 0)
	{
		temp /= 10;
		numDigits++;
	}

	if (num == 0)
	{
		numDigits = 1;
	}

	str = (char *)malloc(numDigits + 1);

	if (str != NULL)
	{
		for (i = numDigits - 1; i >= 0; i--)
		{
			str[i] = '0' + (num % 10);
			num /= 10;
		}
		str[numDigits] = '\0';
	}else
	{
		printf("Memory allocation failed in intToString\n");
	}
	return (str);
}
