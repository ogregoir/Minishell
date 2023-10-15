/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:16:08 by marvin            #+#    #+#             */
/*   Updated: 2023/10/11 12:16:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_export2(t_global *data, char *line)
{
	int	l;

	l = 0;
	while (data->envmini[l] != NULL)
		l++;
	data->envmini[l] = ft_substr(line, 0, ft_strlen(line));
	data->envmini[l + 1] = NULL;
    maj_env_exp(data);
}


int	ft_already_exists(t_global *data, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
    while (data->envmini[j] != NULL)
	{
        if (ft_strncmp(data->envmini[j], str, i) == 0)
        {
            free(data->envmini[j]);
			data->envmini[j] = ft_strdup(str);
            return (4);
        }
        j++;
    }
	return (4);
}



/*
int	ft_export(t_lex *lex, t_global *data)
{
    int j;
    int i;

    j = 0;
	if (!lex->next)
    {
        //ft_print_env(data);
        return (0);
    }
    i = 0;
	j = ft_export4(lex, data, i);
    if (j == 3)
        return (2);
    if (j == 2)
    {
       // printf("-bash: export: `%s': not a valid identifier\n", );
        return (2);
    }
    else
	    return (0);
}*/

int ft_verif_exp(char *str, t_lex *lex)
{
    int     i;

    i = 0;
    if (!lex->next && ft_strchri(str, 61) == -1)
        return (1);
    while (str[i] != '\0')
    {
        if (str[i] == 32)
            return (1);
        if (str[i] == 61)
            break;
        i++;  
    }
    if (ft_strchri(str, 32) != -1)
        return (2);
    return (0);
}

int     ft_export3(t_global *data, char *str)
{
    int i;

    i = 0;
    data->env_exp = malloc(sizeof(char**) + 2);
    while (data->env_exp[i] != NULL)
    {
        if (ft_strncmp(data->env_exp[i], str, ft_strlen(str)) != 0)
        {
            free(data->env_exp[i]);
            data->env_exp[i] = ft_strdup(str);
            data->env_exp[i +1] = NULL;
            return (1);
        }
        i++;
    }
    data->env_exp[i] = ft_strdup(str);
    data->env_exp[i + 1] = NULL;
    return(0);
}