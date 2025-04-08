/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:39:46 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/03 17:49:18 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	malloc_and_qoutelen_double(t_minishell *minishell, \
	char **dest, char *src, int env)
{
	int	k;

	k = ft_quotelen(minishell, src, 1, env);
	*dest = (char *)ft_calloc(1, k + 1);
	if (!(*dest))
		free_and_exit(minishell, 1);
	return (k);
}

static	int	checker_condition(char *src, int *i, int env, int flag)
{
	if ((src[*i] == '$' && !is_escaped(src, *i - 1) && env && \
	(ft_isalnum(src[*i + 1]) || \
		is_char_str(src[*i + 1], "?_"))) && flag == 1)
		return (1);
	if ((src[*i] != '\\' || is_escaped(src, *i - 1) || \
		(src[*i + 1] != '\"' && src[*i + 1] != '\\' \
			&& src[*i + 1] != '$')) && flag == 2)
		return (1);
	return (0);
}

//it is supposed to be is_char_str(src[*i + 1], "?_"
char	*double_quotes(t_minishell *minishell, char *src, int *i, int env)
{
	char	*dest;
	char	*tmp;
	int		k;
	int		j;

	j = 0;
	k = malloc_and_qoutelen_double(minishell, &dest, src + (*i), env);
	while (src[*i] && j < k)
	{
		if (src[*i] == '\"' && !is_escaped(src, *i - 1))
			break ;
		if (checker_condition(src, i, env, 1))
		{
			tmp = replace_env2(minishell, src, i);
			if (tmp)
				j = ft_strlcat(dest, tmp, k);
			free(tmp);
			continue ;
		}
		if (checker_condition(src, i, env, 2) && j < k)
			dest[j++] = src[*i];
		(*i)++;
	}
	dest[j] = '\0';
	return (dest);
}
