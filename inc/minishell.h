/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:53:49 by mdoan             #+#    #+#             */
/*   Updated: 2024/04/26 16:31:01 by mdoan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 42000

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/resource.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_box
{
	char			*name;
	char			*val;
	struct s_box	*next;
}	t_box;

typedef struct s_entry
{
	char			*str;
	char			type;
	struct s_entry	*next;
}	t_entry;

typedef struct s_repos
{
	char			*str;
	int				position;
	struct s_repos	*next;
}	t_repos;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

char	*ft_strdup(const char *s);

void	*ft_memmove(void *dest, void *src, size_t n);
char	*short_str(const char *big, const char *little, size_t len);

void	get_entry(int argc, char **capture);

void	builtins_pwd(void);
void	builtins_env(char **env);
void	builtins_cd(char *str);
void	builtins_echo(char *str);


void	open_prompt(char **env);
void	print_list(t_entry *list_ch);

char	**ft_split(char const *s);

// cd
char	**ft_split_repos(char const *s, char c);
char	**create_repos(void);
void	print_repos(t_repos *list_ch);
char	*list_repos(char **arr);


char	*expand(char *arr, t_box *first);
t_box	*expand_var(char *arr, t_box *first);
void	list_expand(t_entry *list_ch);

char	**create_env(char **env);
int		num_line(char **env);
// t_list	*list_var(char **env);

t_box	*list_var(t_box *first, char *arr_env);
void	print_var(t_box *head);


t_entry	*ft_list(char **arr);

//t_list  *list_variab(char **env);


int		res_equ(char *s, char c);
void	showboxes(t_box *first);
t_entry   *del_elm(t_entry *first);
t_entry     *rep_dol(t_entry *first, t_box *list);
void	builtins_echo_n(char *str);
t_entry *del_pipe(t_entry *first);

#endif
