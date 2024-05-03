/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:45:31 by mdoan             #+#    #+#             */
/*   Updated: 2024/04/23 14:39:42 by mdoan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	totlin(char const *s)
{
	int		begin;
	int		lin;
	int		i;
	int		j;
	int		first_quote;

	begin = 0;
	lin = 0;
	i = 0;
	first_quote = -1;
	while (s[i])
	{
		if (s[i] == ' ')
			begin = 0;
		else if (s[i] == '|')
		{
			begin = 0;
			lin++;
		}
		else if (s[i] == '=')
		{
			begin = 0;
			lin++;
		}
		else if (s[i] == ';')
		{
			begin = 0;
			lin++;
		}
		else if (s[i] == '<' && s[i + 1] != '<')
		{
			begin = 0;
			lin++;
		}
		else if (s[i] == '>' && s[i + 1] != '>')
		{
			begin = 0;
			lin++;
		}
		else if (s[i] == '<' && s[i + 1] == '<')
		{
			begin = 0;
			lin++;
			i++;
		}
		else if (s[i] == '>' && s[i + 1] == '>')
		{
			begin = 0;
			lin++;
			i++;
		}
		else if (s[i] == '\'' && first_quote == -1)
		{
			begin = 0;
			first_quote = i;
			j = i + 1;
			while (s[j])
			{
				if (s[j] == '\'')
				{
					lin++;
					first_quote = -1;
					i = j;
					break ;
				}
				j++;
			}
		}
		else if (s[i] == '\"' && first_quote == -1)
		{
			begin = 0;
			first_quote = i;
			j = i + 1;
			while (s[j])
			{
				if (s[j] == '\"')
				{
					lin++;
					first_quote = -1;
					i = j;
					break ;
				}
				j++;
			}
		}
		else if (s[i] != ' ' && s[i] != '|' && begin == 0)
		{
			begin++;
			lin++;
		}
		i++;
	}
	printf("nombre de lignes : %d\n", lin);
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

static char	*pip(void)
{
	char	*col;

	col = (char *) malloc (2 * sizeof (char));
	if (!col)
		return (NULL);
	col[0] = '|';
	col[1] = '\0';
	return (col);
}

static char	*ega(void)
{
	char	*col;

	col = (char *) malloc (2 * sizeof (char));
	if (!col)
		return (NULL);
	col[0] = '=';
	col[1] = '\0';
	return (col);
}

static char	*pov(void)
{
	char	*col;

	col = (char *) malloc (2 * sizeof (char));
	if (!col)
		return (NULL);
	col[0] = ';';
	col[1] = '\0';
	return (col);
}

static char	*inp(void)
{
	char	*col;

	col = (char *) malloc (2 * sizeof (char));
	if (!col)
		return (NULL);
	col[0] = '<';
	col[1] = '\0';
	return (col);
}

static char	*tru(void)
{
	char	*col;

	col = (char *) malloc (2 * sizeof (char));
	if (!col)
		return (NULL);
	col[0] = '>';
	col[1] = '\0';
	return (col);
}

static char	*her(void)
{
	char	*col;

	col = (char *) malloc (3 * sizeof (char));
	if (!col)
		return (NULL);
	col[0] = '<';
	col[1] = '<';
	col[2] = '\0';
	return (col);
}

static char	*app(void)
{
	char	*col;

	col = (char *) malloc (3 * sizeof (char));
	if (!col)
		return (NULL);
	col[0] = '>';
	col[1] = '>';
	col[2] = '\0';
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

static char	**fill(char const *s, char **arr, size_t clin)
{
	size_t	k;
	int		begin;
	size_t	j;
	int		first_quote;

	k = 0;
	begin = -42;
	j = 0;
	first_quote = -1;
	while (k <= ft_strlen(s))
	{
		if (s[k] == '\"' && first_quote == -1)
		{
			j = k;
			first_quote = k;
			j++;
			while (s[j])
			{
				if (s[j] == '\"')
				{
					arr[clin] = totcol(s, k, j + 1);
					if (mymalloc (arr, clin) == 0)
						return (NULL);	
					clin++;
					begin = -42;
					k = j;
					break ;
				}
				j++;
			}
		}
		else if (s[k] == '\'' && first_quote == -1)
		{
			j = k;
			first_quote = k;
			j++;
			while (s[j])
			{
				if (s[j] == '\'')
				{
					arr[clin] = totcol(s, k, j + 1);
					if (mymalloc (arr, clin) == 0)
						return (NULL);	
					clin++;
					begin = -42;
					k = j;
					break ;
				}
				j++;
			}
		}
		else if ((s[k] == ' ' || k == ft_strlen(s)) && begin != -42)
		{
			arr[clin] = totcol(s, begin, k);
			if (mymalloc (arr, clin) == 0)
				return (NULL);
			clin++;
			begin = -42;
		}
		else if (s[k] == ';' && begin != -42)
		{
			arr[clin] = totcol(s, begin, k);
			clin++;
			arr[clin] = pov();
			if (mymalloc (arr, clin) == 0)
				return (NULL);
			clin++;
			begin = -42;
		}
		else if (s[k] == ';')
		{
			arr[clin] = pov();
			if (mymalloc (arr, clin) == 0)
				return (NULL);
			clin++;
			begin = -42;
		}
		else if (s[k] == '=' && begin != -42)
		{
			arr[clin] = totcol(s, begin, k);
			clin++;
			arr[clin] = ega();
			if (mymalloc (arr, clin) == 0)
				return (NULL);
			clin++;
			begin = -42;
		}
		else if (s[k] == '|' && begin != -42)
		{
			arr[clin] = totcol(s, begin, k);
			clin++;
			arr[clin] = pip();
			if (mymalloc (arr, clin) == 0)
				return (NULL);
			clin++;
			begin = -42;
		}
		else if (s[k] == '|')
		{
			arr[clin] = pip();
			if (mymalloc (arr, clin) == 0)
				return (NULL);
			clin++;
			begin = -42;
		}
		else if (s[k] == '<' && s[k + 1] != '<' && begin != -42)
		{
			arr[clin] = totcol(s, begin, k);
			clin++;
			arr[clin] = inp();
			if (mymalloc (arr, clin) == 0)
				return (NULL);
			clin++;
			begin = -42;
		}
		else if (s[k] == '<' && s[k + 1] != '<')
		{
			arr[clin] = inp();
			if (mymalloc (arr, clin) == 0)
				return (NULL);
			clin++;
			begin = -42;
		}
		else if (s[k] == '>' && s[k + 1] != '>' && begin != -42)
		{
			arr[clin] = totcol(s, begin, k);
			clin++;
			arr[clin] = tru();
			if (mymalloc (arr, clin) == 0)
				return (NULL);
			clin++;
			begin = -42;
		}
		else if (s[k] == '>' && s[k + 1] != '>')
		{
			arr[clin] = tru();
			if (mymalloc (arr, clin) == 0)
				return (NULL);
			clin++;
			begin = -42;
		}
		else if (s[k] == '<' && s[k + 1] == '<' && begin != -42)
		{
			arr[clin] = totcol(s, begin, k);
			clin++;
			arr[clin] = her();
			if (mymalloc (arr, clin) == 0)
				return (NULL);
			clin++;
			begin = -42;
			k++;
		}
		else if (s[k] == '<' && s[k + 1] == '<')
		{
			arr[clin] = her();
			if (mymalloc (arr, clin) == 0)
				return (NULL);
			clin++;
			begin = -42;
			k++;
		}
		else if (s[k] == '>' && s[k + 1] == '>' && begin != -42)
		{
			arr[clin] = totcol(s, begin, k);
			clin++;
			arr[clin] = app();
			if (mymalloc (arr, clin) == 0)
				return (NULL);
			clin++;
			begin = -42;
			k++;
		}
		else if (s[k] == '>' && s[k + 1] == '>')
		{
			arr[clin] = app();
			if (mymalloc (arr, clin) == 0)
				return (NULL);
			clin++;
			begin = -42;
			k++;
		}
		else if ((s[k] != ' ' && s[k] != '|' && begin == -42))
			begin = k;
		k++;
	}
	arr[clin] = 0;
	return (arr);
}

char	**ft_split(char const *s)
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
	arr = (char **) malloc((totlin(s) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (!fill(s, arr, clin))
		return (NULL);
	return (arr);
}
