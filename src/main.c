/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:54:45 by mdoan             #+#    #+#             */
/*   Updated: 2024/04/23 15:16:37 by mdoan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**we_split(char *str)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_split(str);
	while (arr[i])
	{	
		printf("[%s]  ", arr[i]);
		i++;
	}
	printf("\n");
	return (arr);
}

/*
j'ai rajoute le s pour separateur, quand c'est = ou ;
et si ca commence par " alors c'est un argument
*/

char	*search_type(char **arr)
{
	char	*ty;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	ty = (char *) malloc (sizeof (char) * (i + 1));
	ty[i] = '\0';
	i = 0;
	while (arr[i])
	{
		if (*arr[i] == '<')
			ty[i] = 'i';
		else if (arr[i][0] == '<' && arr[i][1] == '<')
			ty[i] = 'h';
		else if (*arr[i] == '>')
			ty[i] = 't';
		else if (arr[i][0] == '>' && arr[i][1] == '>')
			ty[i] = 'd';
		else if (*arr[i] == '|')
			ty[i] = 'p';
		else if (*arr[i] == '=')
			ty[i] = 's';
		else if (*arr[i] == ';')
			ty[i] = 's';
		else if (arr[i][0] == '\"')
			ty[i] = 'g';
		else if (ty[i - 1] == '|' && (*arr[i] != '<' && (arr[i][0] != '<' && arr[i][1] != '<') && *arr[i] != '>' && (arr[i][0] != '>' && arr[i][1] != '>')))
			ty[i] = 'c';
		else if (ty[i - 1] == 'c' || ty[i - 1] == 'i' || ty[i - 1] == 'h' || ty[i - 1] == 't' || ty[i - 1] == 'd')
			ty[i] = 'g';
		else
			ty[i] = 'c';
		i++;
	}
	return (ty);
}

void	print_list(t_entry *list_ch)
{
	while (list_ch != NULL)
	{
		printf("Type: %c, Str: %s\n", list_ch->type, list_ch->str);
		list_ch = list_ch->next;
	}
}

t_entry	*list(char **arr)
{
	t_entry		*list_ch;
	t_entry		*current;
	t_entry		*new;
	int			i;
	char		*ty;

	i = 0;
	list_ch = NULL;
	current = NULL;
	ty = search_type(arr);
	while (arr[i])
	{
		new = malloc(sizeof(t_entry));
		if (new != NULL)
		{
			new->str = arr[i];
			new->type = ty[i];
			new->next = NULL;
		}
		if (list_ch == NULL)
			list_ch = new;
		else
		{
			current = list_ch;
			while (current->next != NULL)
				current = current->next;
			current->next = new;
		}
		i++;
	}
	print_list(list_ch);
	return(list_ch);
}

/*
void	the_argus(char *str)
{
	char	str2[39832];
	int		i;
	int		k;
	int		j;
	int		m;
	int		begin;
	int		begin_value;
	int		end_value;
	// int		begin_name;
	int		end_name;
	
	i = 0;
	j = 0;
	k = 0;
	m = 0;
	begin = -42;

	printf("\n\nstr : %s\n\n", str);
	while (str[i])
	{
		while (str[i] == ' ' && begin == -42)
			i++;
		if (str[i] == ' ' && begin != -42)
			str2[j] = str[i];
		else if (str[i] == '=')
		{
			end_name = i - 1;
			begin = -42;
		}
		else if (str[i] == '"' && begin == -42)
			begin_value = i + 1;
		else if (str[i] == '"' && begin != -42)
		{
			end_value = i - 1;
			begin = -42;
		}
		else
			str2[j] = str[i];
		i++;
		j++;
	}
	ft_strlcat(str2, "\e[0;37m", 32767);
	str2[j] = '\0';
	printf("\n\nstr2 : %s\n\n", str2);
}
*/

		
/*
arg="aa";cd $arg; cd $arg
*/
void	open_prompt(char **env)
{
	char	*str;
	char	**arr;
	char	**repos;
	int		i;
	char	*street;
	
	i = 0;
	while (1)
	{


		// the_argus(str);

		
		repos = create_repos();
		street = list_repos(repos);
		ft_strlcat(street, "\e[0;37m", 32767);
		str = readline(street);
		add_history(str);
		if (ft_strncmp(str, "exit", ft_strlen(str)) == 0) 
			break ;

	
		arr = we_split(str);
		list(arr);

		// Créer un nouveau processus pour exécuter la commande
		pid_t pid = fork();
		if (pid < 0)
			perror("fork");
		else if (pid == 0)
		{
			// Dans le processus enfant : exécuter la commande
			// char *args[] = { "/bin/sh", "-c", str, NULL };
			// execve("/bin/sh", args, NULL);
			exit(EXIT_FAILURE);
		}
		else
		{
			// Dans le processus parent : attendre la fin de l'exécution de la commande
			wait(NULL);
			i = 0;
			while (arr[i])
			{
				
				if (ft_strncmp(arr[i], "cd", ft_strlen(str)) == 0)
					builtins_cd(arr[i + 1]);
				if (ft_strncmp(arr[i], "pwd", ft_strlen(str)) == 0)
					builtins_pwd();
				// ENV DOIT ETRE AU DEBUT DE ARR[i] OU BIEN APRES UN PIPE
				if (ft_strncmp(arr[i], "env", ft_strlen(str)) == 0)
					builtins_env(env);
				if ((ft_strncmp(arr[i], "echo", ft_strlen(str)) == 0) && (ft_strncmp(arr[i + 1], "-n", ft_strlen(str)) == 0))
					builtins_echo(arr[i + 2]);
				if (arr[i][0] == '$')
				{
				 	expand(arr[i]);
				}
						
				i++;
			}
			list_expand(list(arr));
		}
	}
}

int	main(int argc, char *argv[], char **env)
{
	(void) argc;
	(void) argv;
	open_prompt(env);
}
