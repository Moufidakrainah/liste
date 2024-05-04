/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:54:45 by mdoan             #+#    #+#             */
/*   Updated: 2024/04/26 17:13:59 by mdoan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		j;

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
		//else if (*arr[i] == '=')
			//ty[i] = 's';
		else if (*arr[i] == ';')
			ty[i] = 's';
		else if (arr[i][0] == '\"')
			ty[i] = 'g';
		else if (ty[i - 1] == '|' && (*arr[i] != '<' && (arr[i][0] != '<' && arr[i][1] != '<') && *arr[i] != '>' && (arr[i][0] != '>' && arr[i][1] != '>')))
			ty[i] = 'c';
		else if (ty[i - 1] == 'c' || ty[i - 1] == 'i' || ty[i - 1] == 'h' || ty[i - 1] == 't' || ty[i - 1] == 'd')
			ty[i] = 'g';
		else
		{
			j = 0;
			while (arr[i][j])
			{
				if (arr[i][j] == '=')
				{
					ty[i] = 'g';
					break ;
				}
				j++;
			}
			if (arr[i][j] == '\0')
				ty[i] = 'c';
		}
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

t_entry	*ft_list(char **arr)
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
	//print_list(list_ch);
	return(list_ch);
}


void	open_prompt(char **env)
{
	int		i;
	char	*str;
	char	**arr;
	char	**repos;
	char	*street;
	t_box	*list = NULL;
	t_entry *list_str = NULL;
	t_entry	*listf= NULL;
	t_entry *listp = NULL;
	t_entry *exec = NULL;
	char	**table;
	table = create_env(env);
	if (table == NULL)
	{
		printf("vide\n");
		return ;
	}
	i = 0;
	while (table[i])
	{
		list = list_var(list, table[i]);
		i++;
	}
	i = 0;
	while (1)
	{
		repos = create_repos();
		street = list_repos(repos);
		ft_strlcat(street, "\e[0;37m", 32767);
		str = readline(street);
		add_history(str);

		if (strcmp(str, "e") == 0) 
			break ;
		arr = we_split(str);
		list_str = ft_list(arr);
		print_list(list_str);
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
			while (list_str != NULL)
			{
				
				if (strcmp(list_str->str, "env") == 0)
				{
					showboxes(list);
		
				}

				/*if (list_str->type == 's')
				{
					printf("affiche un message d'erreur");
					return ;
				}*/
				if (list_str->type == 'g' &&  res_equ(list_str->str, '=') != 0)  // on recupere le type pour faire expand_var sinon ca cree un noeud (une box) vide avec =
				{
					list = list_var(list, list_str->str);
					//showboxes(list);
				
				}
				//printf("%s\n", list_str->str);
				list_str=list_str->next;
			}
		}
		list_str = ft_list(arr);
		printf("La liste sans les arguments avec '=' :\n");
		listf = del_elm(list_str);
		print_list(listf);
		listp = del_pipe(listf);
		printf("suppression des pipes\n");
		print_list(listp);
		exec = rep_dol(listp, list);
		printf ("La liste avec remplacement du $ avec le contenu de la variable: \n");
		print_list(exec);
		while (exec!= NULL)
			{
				if (strcmp(exec->str, "cd") == 0)
					builtins_cd(exec->next->str);
				if (strcmp(exec->str, "pwd") == 0)
					builtins_pwd();
				// ENV DOIT ETRE AU DEBUT DE ARR[i] OU BIEN APRES UN PIPE
				/*if (ft_strncmp(ist_str->str, "env") == 0)
					builtins_env(env);*/
				if ((strcmp(exec->str, "echo") == 0) && (strcmp(exec->next->str, "-n") == 0))
				{
					printf("execution de la commande echo -n \n");
					builtins_echo_n(exec->next->next->str);
				}
				if (strcmp(exec->str, "echo") == 0)
				{
					printf("execution de la commande echo \n");
					builtins_echo(exec->next->str);
				}
				exec=exec->next;
			}
			
	}	
}

int	main(int argc, char *argv[], char **env)
{
	(void) argc;
	(void) argv;
	open_prompt(env);
}
