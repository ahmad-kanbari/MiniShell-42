/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:37:08 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/02 16:42:08 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_iswhitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	find_token(char **ps, char *es, char *tokens)
{
	char	*s;

	s = *ps;
	while (s < es && ft_iswhitespace(*s))
		s++;
	*ps = s;
	return (*s && ft_strchr(tokens, *s));
}
