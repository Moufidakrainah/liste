/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:18:03 by mdoan             #+#    #+#             */
/*   Updated: 2024/04/23 11:06:12 by mdoan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../inc/minishell.h"
#include "inc/minishell.h"

void	builtins_pwd(void)
{
	char	buf[BUFFER_SIZE];

	getcwd(buf, BUFFER_SIZE);
	printf("%s\n", buf);
}

void	builtins_env(char **env)
{	
	int		i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	builtins_cd(char *str)
{
	chdir(str);
}

void	builtins_echo(char *str)
{
	printf("%s", str);
}
