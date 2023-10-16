/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:09:54 by marvin            #+#    #+#             */
/*   Updated: 2023/10/13 14:09:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    maj_env_exp(t_global *data)
{
    int l;

    l = 0;
    while (data->env_exp[l] != NULL)
    {
        free(data->env_exp[l]);
        data->env_exp[l] = ft_strdup(data->envmini[l]);
        l++;
    }
    if (data->env_exp[l] == NULL && data->envmini[l] != NULL)
    {
        while (data->envmini[l] != NULL)
        {
            data->env_exp[l] = ft_strdup(data->envmini[l]);
            l++;
        }
        data->env_exp[l] = NULL;
    }
}

char    *ft_env_exp(char *line, t_global * data)
{
    int i;
    int j;
    char    *str;

    i = 0;
    j = 0;
    str = NULL;
    while (data->env_exp[j] != NULL)
    {
        printf("dataenve %s\n", data->env_exp[j]);
        j++;
    }
    j = 0;
    if (ft_strchri(line, 61) == -1)
    {
        i = ft_strlen(line);
	    while (data->env_exp[j] != NULL)
	    {
            printf("data %s\n", data->env_exp[j]);
		    if (ft_strncmp(line, data->env_exp[j], i) == 0)
            {
                str = ft_strdup(data->env_exp[j]);
                free (data->env_exp[j]);
                printf("strr %s\n", str);
                return (str);
            }
            j++;
		}
        if (data->env_exp[j] == NULL)
            return(line);
    }
    else
    {
        while (line[i] != '=')
		    i++;
        i++;
        return (line);
	}
    return ("NULL");
}

int ft_export4(t_lex *lex, t_global *data, int i)
{
    char    *str;

    str = NULL;
    (void)i;
    if (ft_env_exp(lex->next->content, data) != NULL)
    {
        str = ft_env_exp(lex->next->content, data);
        printf("str1 %s\n", str);
    }
    else
        return (8);
    lex = lex->next;
    if (lex->content[0] == 61)
    {
        str = ft_strdup(lex->content);
        if (lex->next->content != NULL)
        {
            lex = lex->next;
            return (2);
        }
        else
        {
            printf("-bash: export: `%s\n': not a valid identifier", str);
            return (3);
                
        }
    }
	if (ft_already_exists(data, str) == 4)
        ft_export2(data, str);
	else if (ft_already_exists(data, str) != 1)
        i = ft_already_exists(data, str);
    if (!lex->next)
        return (8);
    else
        ft_export4(lex, data, i);
    if (i == 0)
        return (0);
    return (0);
}

int	ft_export(t_lex *lex, t_global *data)
{
    int j;
    int     i;
    char    *str;

    
    j = 0;
    i = 0;
	if (!lex->next)
    {
        while (data->envmini[i] != NULL)
        {
            printf("declare -x %s\n", data->envmini[i]);
            i++;
        }
        return (0);
    }
    while (lex->content != NULL)
    {
        maj_env_exp(data);
        j = ft_export4(lex, data, i);
        printf("%d\n", j);
        lex = lex->next;
    }
    str = ft_env_exp(lex->next->content, data);
    printf("str %s\n", str);
    return (1);
	
    if (j == 3)
        return (2);
    if (j == 2)
    {
        //printf("-bash: export: `%s': not a valid identifier\n", );
        return (2);
    }
    else
	    return (0);
}