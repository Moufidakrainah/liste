/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:39:56 by mdoan             #+#    #+#             */
/*   Updated: 2024/04/23 11:06:16 by mdoan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*expand(char *arr)
{
	char	name[ft_strlen(arr)];
	char	*value;
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (arr[i])
		name[j++] = arr[i++];
	name[j] = '\0';
	printf("name of variable %s : \n", name);
	i = 0;
	value = malloc(sizeof(char) * (ft_strlen(getenv(name))) + 1);
	while ((getenv(name))[i])
	{
		value[i] = (getenv(name))[i];
		i++;
	}
	value[i] = '\0';
	printf("value of variable %s : \n", value);
	return(value);
}

char	*expand_var(char *arr, char *equ, char *val)
{
	char	str[ft_strlen(arr)];
	char	*value;
	int		i;
	int		j;
	
	i = 1;
	j = 0;
	value = malloc (sizeof(char) * (32767 + 1));
	value[32767] = '\0';
	while (arr[i])
		str[j++] = arr[i++];
	str[j] = '\0';
	printf("name of variable %s : \n", str);
	// si cette chaine commence par $ et il ya un = dedans
	i = 1;
	//voir le cas plein d espace avant..............
	if (arr[0] == '$' && equ[0] == '=' && val[0] == '"')
	{
		j = 0;
		while (val[i] != '"')
		{
			value[j] = val[i];
			i++;
			j++;
		}
		value[j] = '\0';
	}
	printf("value of variable %s : \n", value);
	return(value);
}

void print_list_var(t_entry *list) {
    printf("Printing expanded list:\n");
    t_entry *current = list;
    while (current != NULL) {
        printf("Type: %d, StrVar: %s\n", current->type, current->str);
        current = current->next;
    }
}

void	list_expand(t_entry *list_ch)
{
	t_entry		*list;
	t_entry		*current;
	t_entry		*new;

	list = NULL;
	current = NULL;
	while (list_ch != NULL)
	{
		new = malloc(sizeof(t_entry));
		if (new != NULL)
		{
			if (list_ch != NULL && list_ch->str[0] == '$')
			{
				char *expand_str = expand(list_ch->str);
				if (expand_str != NULL)
				{
					new->str = strdup (expand_str);
					printf("str list 1 = %s et str expand list = %s\n", list_ch->str, new->str);
					new->type = list_ch->type;
					printf("type liste 1 = %c et type expand list = %c\n", list_ch->type, new->type);
					new->next = NULL;
				}
				else
				{
					free(new);
					continue;
				}
			}
			else
			{
				new->str = strdup(list_ch->str);
				printf("str list 1 = %s et str expand list = %s\n", list_ch->str, new->str);
				new->type = list_ch->type;
				printf("type liste 1 = %c et type expand list = %c\n", list_ch->type, new->type);
				new->next = NULL;
			}

			if (list == NULL)
			list = new;
			else
			{
				current = list;
				while (current->next != NULL)
					current = current->next;
				current->next = new;
			}
		}
		else
		{
			fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
		}
		list_ch = list_ch->next;
	}
}


