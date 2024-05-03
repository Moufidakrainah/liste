/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:33:53 by mdoan             #+#    #+#             */
/*   Updated: 2024/04/23 11:06:24 by mdoan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**create_repos(void)
{
	char	**arr;
	//int		i;
	char	buf[BUFFER_SIZE];

	//i = 0;
	getcwd(buf, BUFFER_SIZE);
	arr = ft_split_repos(buf, '/');
	// while (arr[i])
	// {	
	// 	printf("%s --> ", arr[i]);
	// 	i++;
	// }
	// printf("\n");
	return (arr);
}

void	print_repos(t_repos *list_ch)
{
	while (list_ch != NULL)
	{
		// printf("Str: %s\n", list_ch->str);
		list_ch = list_ch->next;
	}
}

char	*list_repos(char **arr)
{
	t_repos		*list_ch;
	t_repos		*current;
	t_repos		*new;
	int			i;
	char		*street;

	i = 0;
	list_ch = NULL;
	current = NULL;
	street = (char *) malloc (sizeof (char) * (32767 + 1));
	street[32767] = '\0';
	while (arr[i])
	{
		new = malloc(sizeof(t_repos));
		if (new != NULL)
		{
			ft_strlcat(street, "/", 32767);
			new->str = arr[i];
			new->position = i;
			new->next = NULL;
			ft_strlcat(street, new->str, 32767);
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
	ft_strlcat(street, " $ ", 32767);
	// print_repos(list_ch);
	street = short_str(street, getenv("HOME"), ft_strlen(street));
	return (street);
}
