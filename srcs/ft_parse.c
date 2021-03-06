/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcajee <tcajee@student.wethinkcode.co.za>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 12:52:36 by tcajee            #+#    #+#             */
/*   Updated: 2020/04/27 12:52:36 by tcajee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/incs/libft.h"

char    *parse_vars(char *temp, char *str, char **envv)
{
    int   i;
    char  *end;
    char  *key;
    char  *out;
    char  **envt;

    i = -1;
    out = NULL;
    if (!(end = ft_strchr(str, ' ')))
        end = (str[ft_strlen(str) - 1] == '\n') ? &str[ft_strlen(str) - 1]
            : &str[ft_strlen(str)];
    key = ft_strsub(str, 0, end - str);
    while (envv && envv[++i])
    {
        envt = ft_strsplit(envv[i], '=');
        if (!(ft_strcmp(envt[0], key)))
            out = ft_strjoin(temp, ft_strchr(envv[i], '=') + 1);
        arr_del(envt);
        if (out)
            break;
    }
    (!out) ? out = ft_strdup(temp) : NULL;
    (key) ? free(key) : NULL;
    (temp) ? free(temp) : NULL;
    return (out);
}

char   *parse_line(char *line, char **envv)
{
    int     i;
    char    *temp;

    i = 0;
    temp = ft_strnew(0);
    while (line[i])
    {
        if (line[i] == '$' && line[i + 1] && !ft_isspace(line[i + 1]))
        {
          temp = parse_vars(temp, &line[i + 1], envv);
          while (line[i + 1] && !ft_isspace(line[i + 1]) && line[i + 1] != '$')
              i++;
        }
        else if (((i && ft_isspace(line[i - 1])) || i == 0) && line[i] == '~')
            temp = parse_vars(temp, "HOME", envv);
        else
            temp = char_add(temp, line[i]);
        i++;
    }
    (line) ? free(line) : NULL;
    return (temp);
}
