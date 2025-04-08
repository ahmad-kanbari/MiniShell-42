/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:38:46 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/04 13:10:56 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	no_quotes_helper(t_minishell *m, char *src)
{
	while (src[*(m->q->i)] && m->q->j < m->q->k)
	{
		if ((src[*(m->q->i)] == '\'' || src[*(m->q->i)] == '\"') && \
			!is_escaped(src, *(m->q->i) - 1))
			break ;
		if (src[*(m->q->i)] == '$' && !is_escaped(src, *(m->q->i) \
			- 1) && m->q->env && (ft_isalnum(src[*(m->q->i) + 1]) \
				|| is_char_str(src[*(m->q->i) + 1], "?_")))
		{
			m->q->tmp = replace_env2(m, src, (m->q->i));
			if (m->q->tmp)
				m->q->j = ft_strlcat(m->q->dest, m->q->tmp, m->q->k);
			else
			{
				ft_strdel(&m->q->dest);
				break ;
			}
			free(m->q->tmp);
			continue ;
		}
		if ((src[*(m->q->i)] != '\\' || \
			is_escaped(src, *(m->q->i) - 1)) && m->q->j < m->q->k)
			m->q->dest[m->q->j++] = src[*(m->q->i)];
		(*(m->q->i))++;
	}
}

char	*no_quotes(t_minishell *minishell, char *src, int *i, int env)
{
	char	*dest;
	int		k;
	int		j;

	j = 0;
	k = ft_quotelen(minishell, src + *i, 0, env);
	dest = (char *)ft_calloc(1, k + 5);
	if (!dest)
		free_and_exit(minishell, minishell->exit);
	minishell->q = ft_calloc(1, sizeof(t_parsing_q));
	minishell->q->k = k;
	minishell->q->dest = dest;
	minishell->q->j = j;
	minishell->q->env = env;
	minishell->q->i = i;
	minishell->q->tmp = NULL;
	no_quotes_helper(minishell, src);
	if (!minishell->q->dest)
		return (NULL);
	minishell->q->dest[minishell->q->j] = '\0';
	dest = minishell->q->dest;
	free(minishell->q);
	return (dest);
}
