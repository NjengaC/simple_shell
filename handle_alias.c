#include "shell.h"
int handle_alias (char **av)
{
	if (av[1])
	{
		if (av[2])
		{

			if (add_alias(av[1], av[2]) == 0)
			{
				printf("Alias added: %s='%s'\n", av[1], av[2]);
			}
			else
			{
				printf("Error: Cannot add alias; alias limit reached.\n");
			}
		}
		else
		{
			printf("Usage: alias [name[='value'] ...]\n");
		}
	}
	else
	{
		list_aliases();
	}
	return (0);
}

int add_alias(const char *name, const char *value)
{
	if (num_aliases >= MAX_ALIASES)
	{
		return -1;
	}

	aliases[num_aliases].name = strdup(name);
	aliases[num_aliases].value = strdup(value);

	num_aliases++;
	return (0);
}

int remove_alias(const char *name)
{
	int i, j;

	for (i = 0; i < num_aliases; i++)
	{
		if (strcmp(aliases[i].name, name) == 0)
		{
			free(aliases[i].name);
			free(aliases[i].value);
			num_aliases--;

			for (j = i; j < num_aliases; j++)
			{
				aliases[j] = aliases[j + 1];
			}
			return 0;
		}
	}
	return -1;
}

void list_aliases()
{
	int i;

	for (i = 0; i < num_aliases; i++)
	{
		printf("alias %s='%s'\n", aliases[i].name, aliases[i].value);
	}
}

const char *lookup_alias(const char *name)
{
	int i;

	for (i = 0; i < num_aliases; i++)
	{
		if (strcmp(aliases[i].name, name) == 0)
		{
			return aliases[i].value;
		}
	}
	return NULL;
}
