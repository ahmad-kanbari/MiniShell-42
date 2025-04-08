/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:22:27 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/02 17:56:17 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*replace_env(t_minishell *minishell, char *str, int i)
{
	int		k;
	int		j;
	char	*tmp;
	char	*new;

	k = ft_quotelen(minishell, str, 4, 1);
	new = (char *)ft_calloc(1, k + 1);
	if (!(new))
		free_and_exit(minishell, 1);
	j = 0;
	while (str[i] && j < k)
	{
		if (str[i] == '$' && !is_escaped(str, i - 1))
		{
			tmp = replace_env2(minishell, str, &i);
			j = ft_strlcat(new, tmp, k);
			free(tmp);
			continue ;
		}
		if ((str[i] != '\\' || is_escaped(str, i - 1)) && j < k)
			new[j++] = str[i];
		i++;
	}
	free(str);
	return (new);
}

char	*replace_env2(t_minishell *minishell, char *str, int *i)
{
	int		count;
	char	buf[4096];
	char	*new;
	char	*env_value;

	new = ft_strdup("");
	count = 0;
	(*i)++;
	ft_bzero(buf, sizeof(buf));
	while (str[*i] && (ft_isalnum(str[*i]) || is_char_str(str[*i], "?_")))
	{
		buf[count] = str[*i];
		*i = *i + 1;
		if (str[*i - 1] == '?' && count == 0)
			break ;
		if (ft_isdigit(str[*i - 1]) && count == 0)
			return (new);
		count++;
	}
	env_value = getenv_value(minishell, buf, minishell->env_list);
	if (env_value)
		new = ft_strjoin_one_free(new, (env_value));
	else
		ft_strdel(&new);
	return (new);
}
