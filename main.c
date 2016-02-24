//
// HEADER
//

#include <stdlib.h> // malloc, NULL
#include <stdio.h> // printf

void	print_tab(char **tab) // test
{
	int i;
	int len;

	i = 0;
	len = tab_len(tab);
	printf("\n");
	if (*tab && tab)
	{
		while (i < len)
		{
			printf("tab[%d] = %s\n", i, tab[i]);
			i++;
		}
	}
	else
		printf("no cpy of **env\n");
	printf("\n");
}

int	tab_len(char **tab)
{
	int len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

char	**cpy_env(char **env)
{
	int	i;
	int	len;
	char	**cpy;

	if (!(*env) || !env)
		return (NULL);
	else
	{
		i = 0;
		len = tab_len(env);
		if (!(cpy = (char **)malloc(sizeof(char) * len + 1)))
			return (NULL);
		while (i < len)
		{
			cpy[i] = env[i];
			i++;
		}
		cpy[i] = NULL;
	}
	return (cpy);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	char	**env_cpy;

	print_tab(env); // test
	env_cpy = cpy_env(env);
	print_tab(env_cpy); // test
	return (0);
}
