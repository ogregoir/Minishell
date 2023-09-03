/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 03:39:56 by marvin            #+#    #+#             */
/*   Updated: 2023/08/29 03:39:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char  *ft_back(char *buf)
{
    int     i;
    char    *newbuf;

    i = ft_strlen(buf);
    newbuf = malloc((ft_strlen(buf)) - 1);
    while(buf[i] != 47)
        i--;
    newbuf = ft_substr(buf, 0, i);
    return(newbuf);
}

char    *ft_forward(char *buf, char **line)
{
    char    *temp;
    char    *newbuf;
    char    *bis;
    int     i;

   i = ft_strlen(buf);
   temp = malloc(i + ft_strlen(line[1]) +1);
   ft_strlcpy(temp, buf, i +1);
   temp[i] = 47;
   temp[i +1] = '\0'; 
   bis = ft_substr(line[1], 0, (ft_strlen(line[1]) -1));
   newbuf = ft_strjoin(temp, bis);
   free(temp);
   free (bis);
   return (newbuf);
}

void ft_cd(char **line, char *buf, t_cd * path)
{
    char    *temp;

    temp = ft_substr(buf, 0, ft_strlen(buf));
   	if (line[1] == NULL || line[1][0] == 126)
		buf = getenv("HOME");
    else if (ft_strncmp(line[1], "..", ft_strlen(line[1])) == 0)
        buf = ft_back(buf);
    else if (line[1][0] == 47)
        buf = ft_substr(line[1], 0, ft_strlen(line[1]));
    else if (ft_isalnum(line[1][0]) != 0)
        buf = ft_forward(buf, line);
    else if (line[1][0] == 45)
    {
        if (path->old_buf == NULL)
            printf("-bash: cd: OLDPWD not set\n");
        else
            buf = ft_substr(path->old_buf, 0, ft_strlen(path->old_buf));
    }
        
    if (access(buf, X_OK | F_OK) == 0 && buf != NULL)
    {
        path->old_buf = ft_substr(temp, 0, ft_strlen(temp));
        chdir(buf);
    } 
    else
        printf("minishell: cd: %s: No such file or directory\n", buf);
    free(buf);
    free(temp);
}