/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:18:03 by mdoan             #+#    #+#             */
/*   Updated: 2024/04/26 11:53:22 by mdoan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_pwd()
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

void	builtins_echo_n(char *str)
{
	printf("%s", str);
}

void	builtins_echo(char *str)
{
	printf("%s\n", str);
}