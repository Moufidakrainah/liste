#include "minishell.h"

int num_line(char **env)
{	
	int		i;

	i = 0;
	while (env[i])
        i++;
    return (i);
}

char	**create_env(char **env)
{	
	int		i;
    int     j;
    char    **arr_env;

	i = 0;
    arr_env = malloc (sizeof(char *) * (num_line(env) + 1));
	if (env[i] == NULL)
		return (NULL);
	while (env[i])
	{
        j = 0;
        while (env[i][j])
            j++;
        arr_env[i] = malloc (sizeof(char) * (j + 1));
        j = 0;
        while (env[i][j])
        {
            arr_env[i][j] = env[i][j];
            j++;
        }
        arr_env[i][j] = '\0';
		i++;
	}
    arr_env[i] = 0;
    return (arr_env);
}


t_box *list_var(t_box *first, char *arr_env)
{
    char **tab;
    t_box   *b;
    t_box   *temp;
    int check = 0;
	
    tab = ft_split_repos(arr_env, '=');
	b = (t_box *)malloc (sizeof(t_box));
	b->name = tab[0];
	b->val = tab[1];
    b->next = NULL;

    if (first== NULL)
        first = b;
    else
    {
        temp = first;
        while (temp->next != NULL)
        {
            if (strcmp(b->name, temp->name) == 0)
            {
                temp->val = b->val;
                check = 1;
            }
            temp = temp->next;
        }
        if (temp->next == NULL && (strcmp(b->name, temp->name)) == 0)
        {
            temp->val = b->val;
            check = 1;
        }
        
        if (check == 0)
        {
            temp->next = b;
        }   
    } 
    return (first);
}

/*t_entry   *del_elm(t_entry *first)
{
    t_entry   *temp;
    t_entry   *p;
    t_entry     *head;
    if (first != NULL)
    {
        if (res_equ(first->str, '=') != 0 && first->next == NULL)
        {
            p = first;
            first = first->next;
            free(p);
        }
        if (res_equ(first->str, '=') != 0 && first->next != NULL && first->next->next != NULL)
        {
            p = first;
            first = first->next;
            free(p);
            p = first;
            first = first->next;
            free(p);
            continue;
        }
        else 
        {
            temp = first;
            while (temp->next != NULL && res_equ(temp->next->str, '=') == 0)
            temp = temp->next;
            if (temp->next != NULL && temp->next->next != NULL ) 
            {
                p = temp->next;
                temp->next = temp->next->next;
                free(p);
                p = temp->next;
                temp->next = temp->next->next;
                free(p);

            }
            else if (temp->next != NULL && temp->next->next == NULL )  
            {
                p = temp->next;
                temp->next = temp->next->next;
                free(p);
            }
        }  

    }
    return(first);
}*/

t_entry   *del_elm(t_entry *first)
{
    t_entry   *p =first;
    t_entry    **prev = &first;

    while (p)
    {
        while (p &&( res_equ(p->str, '=') == 0))
        {
            
            prev = &(p->next);
            p = p->next;
            printf("pas de = \n");
        }

        if(p) 
        {
            
            *prev = p->next;
            free(p);
            p= *prev;
            printf("ya un egal\n");
        } 
        printf ("on boucle\n"); 

    }
    return(first);
}

t_entry *del_pipe(t_entry *first)
{
    t_entry   *p =first;
    t_entry    **prev = &first;

    while (p)
    {
        while (p && p->str[0] != '|')
        {
            
            prev = &(p->next);
            p = p->next;
            printf("pas de pipe \n");
        }

        if(p) 
        {
            
            if ((p->next) && (p->next->str[0] == '|'))
            {
                *prev = p->next;
                free(p);
                p= *prev;
                printf("ya un pipe\n");

            }
            else if (p->next == NULL)
            {
                *prev = p->next;
                free(p);
                p= *prev;
                printf("ya un pipe\n");

            }
            else
            {
                prev = &(p->next);
                p = p->next;
                printf ("c'est le dernier pipe");
            }
        } 
        printf ("on boucle\n"); 

    }
    return(first);
}


t_entry     *rep_dol(t_entry *first, t_box *list)
{
    t_entry     *temp;
    char        *variable;
    int         i;
    int         j;

    temp = first;
    if (first != NULL)
    {
        while (temp != NULL)
        {
            if (temp->str[0] == '$' )
            {
                variable = malloc(sizeof(char) * ft_strlen(temp->str));
                i = 1;
                j = 0;
                while (temp->str[i])
                {
                    variable[j] = temp->str[i];
                    i++;
                    j++;
                }
                variable[j] = '\0';
                while (list != NULL)
                {
                    if (strcmp(list->name, variable) == 0)
                        strcpy(temp->str, list->val);
                    list = list->next;
                }
            }
             temp = temp->next;
        }
     }
    return (first);
}

void showboxes(t_box *first)
{
    t_box *isee;

    isee = first;
    if (isee == NULL)
        printf("Empty list");
    else
    {
        while (isee != NULL)
        {
            printf("%s = %s\n", isee->name, isee->val);
            isee = isee->next;
        }
    }
}