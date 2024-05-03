/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:56:10 by mdoan             #+#    #+#             */
/*   Updated: 2024/04/23 11:06:44 by mdoan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		c;

	i = 0;
	c = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] == s2[i])
		{
			i++;
		}
		else if (s1[i] < s2[i])
		{
			c = (unsigned char) s2[i] - (unsigned char) s1[i];
			c *= (-1);
			return (c);
		}
		else if (s1[i] > s2[i])
		{
			c = (unsigned char) s1[i] - (unsigned char) s2[i];
			return (c);
		}
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	idst;

	i = 0;
	idst = ft_strlen(dst);
	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	while (src[i] != '\0' && (idst + i + 1) < size)
	{
		dst[idst + i] = src[i];
		i++;
	}
	dst[idst + i] = '\0';
	return (ft_strlen(src) + idst);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*short_str(const char *big, const char *little, size_t len)
{
	size_t	b;
	size_t	l;
	char	*street;

	street = (char *) malloc (sizeof (char) * (32767 + 1));
	ft_strlcat(street, "\e[0;33m", 32767);
	ft_strlcat(street, getenv("USER"), 32767);
	ft_strlcat(street, "@", 32767);
	char s1[32767];
	ft_strlcat(s1, getenv("SESSION_MANAGER"), 32767);
	char **arr;
	arr = ft_split_repos(s1, ':');
	char **arr2;
	arr2 = ft_split_repos(arr[0], '/');
	ft_strlcat(street, arr2[1], 32767);
	ft_strlcat(street, ":", 32767);
	b = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (big[b])
	{	
		l = 0;
		while (big[b + l] == little[l] && (b + l) < len && little[l] != '\0')
			l++;
		if (l == ft_strlen(little))
		{
			ft_strlcat(street, "\e[1;34m", 32767);
			ft_strlcat(street, (char *)&big[l + 1], 32767);
			return (street);
		}
		b++;
	}
	return (NULL);
}

void	*ft_memmove(void *dest, void *src, size_t n)
{
	unsigned char	*dest1;
	unsigned char	*src1;
	size_t			i;

	dest1 = (unsigned char *) dest;
	src1 = (unsigned char *) src;
	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			dest1[i] = src1[i];
			i++;
		}
	}
	else if (src < dest)
	{
		while (i < n)
		{
			dest1[n - 1] = src1[n - 1];
			n--;
		}
	}
	return (dest);
}
