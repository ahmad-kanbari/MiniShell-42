/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:38:26 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/03 16:48:49 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_quotelen(t_minishell *minishell, char *src, int type, int env)
{
	int	i;
	int	j;
	int	esc;

	i = 0;
	j = 0;
	esc = 0;
	while (src[i])
	{
		if (!esc && src[i] == '\'' && type == 2)
			return (i);
		if (!esc && src[i] == '\'' && type == 0)
			return (i + j);
		if (!esc && src[i] == '$' && (type == 0 || type == 1 || type == 4) && \
			env)
			j += ft_envlen(minishell, src, i);
		if (!esc && src[i] == '\"' && (type == 0 || type == 1))
			return (i + j);
		esc = 0;
		if (src[i] == '\\' && type != 2)
			esc = 1;
		i++;
	}
	return (i + j);
}

char	*simple_qoutes(t_minishell *minishell, char *src, int *i)
{
	char	*dest;
	int		j;

	(*i)++;
	j = ft_quotelen(minishell, src + *i, 2, 0);
	dest = (char *)ft_calloc(1, j + 1);
	if (!(dest))
		free_and_exit(minishell, 1);
	j = 0;
	while (src[*i] && src[*i] != '\'')
	{
		dest[j] = src[*i];
		*i = *i + 1;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

static	char	*handle_qoutes_simple(t_minishell *minishell, \
	char *src, char *dest, int *i)
{
	char	*tmp;

	tmp = simple_qoutes(minishell, src, i);
	dest = ft_strjoin_double_free(&dest, &tmp);
	return (dest);
}

static	char	*handle_qoutes_helper(t_minishell *minishell, \
	char *src, char *dest, int env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (src[i])
	{
		if (src[i] == '\'' && !is_escaped(src, i - 1))
			dest = handle_qoutes_simple(minishell, src, dest, &i);
		else if (src[i] == '\"' && !is_escaped(src, i - 1))
		{
			i++;
			tmp = double_quotes(minishell, src, &i, env);
			dest = ft_strjoin_double_free(&dest, &tmp);
		}
		else
		{
			tmp = no_quotes(minishell, src, &i, env);
			if (tmp)
				dest = ft_strjoin_double_free(&dest, &tmp);
			continue ;
		}
		if (src[i])
			i++;
	}
	return (dest);
}

char	*handle_quotes(t_minishell *minishell, char *src, int env)
{
	char	*dest;

	if (src == NULL)
		return (src);
	dest = ft_strdup("");
	dest = handle_qoutes_helper(minishell, src, dest, env);
	ft_strdel(&src);
	return (dest);
}
