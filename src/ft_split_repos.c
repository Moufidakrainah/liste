/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_repos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:16:49 by mdoan             #+#    #+#             */
/*   Updated: 2024/04/23 11:06:27 by mdoan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	totlin(char const *s, char c)
{
	int		begin;
	int		lin;

	begin = 0;
	lin = 0;
	while (*s)
	{
		if (*s == c)
			begin = 0;
		else if (*s != c && begin == 0)
		{
			begin++;
			lin++;
		}
		s++;
	}
	return (lin);
}

static char	*totcol(char const *s, int begin, int end)
{
	char	*col;
	int		k;

	k = 0;
	col = (char *) malloc ((end - begin + 1) * sizeof (char));
	if (!col)
		return (NULL);
	while (begin < end)
	{
		col[k] = s[begin];
		k++;
		begin++;
	}
	col[k] = '\0';
	return (col);
}

static int	mymalloc(char **arr, int clin)
{
	int	i;

	i = 0;
	if (!arr[clin])
	{
		while (i < clin)
		{
			free(arr[i]);
			i++;
		}
		free (arr);
		return (0);
	}
	return (1);
}

static char	**fill(char const *s, char c, char **arr, size_t clin)
{
	size_t	k;
	int		begin;

	k = 0;
	begin = -42;
	while (k <= ft_strlen(s))
	{
		if ((s[k] == c || k == ft_strlen(s)) && begin != -42)
		{
			arr[clin] = totcol(s, begin, k);
			if (mymalloc (arr, clin) == 0)
				return (NULL);
			clin++;
			begin = -42;
		}
		else if ((s[k] != c && begin == -42))
			begin = k;
		k++;
	}
	arr[clin] = 0;
	return (arr);
}

char	**ft_split_repos(char const *s, char c)
{
	char	**arr;
	size_t	clin;

	clin = 0;
	if (!s || s[0] == '\0' || !*s)
	{
		arr = (char **) malloc (sizeof (char *));
		if (arr)
			arr[0] = NULL;
		return (arr);
	}
	arr = (char **) malloc((totlin(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (!fill(s, c, arr, clin))
		return (NULL);
	return (arr);
}
