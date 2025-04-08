/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_valid_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:49:10 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/03 18:11:11 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	contains_unbalanced_quotes(char *buf, t_minishell *shell)
{
	int	i;
	int	tok;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\"' || buf[i] == '\'')
		{
			tok = buf[i];
			i++;
			while (buf[i] && buf[i] != tok)
				i++;
			if (!buf[i])
			{
				ft_printf_fd(STDERR_FILENO, "minishell: unexpected EOF while looking \
for matching `%c'\n", tok);
				shell->exit = 258;
				return (1);
			}
			i++;
		}
		else
			i++;
	}
	return (0);
}

int	validate_command(char *buf, t_minishell *shell)
{
	if (contains_unbalanced_quotes(buf, shell))
		return (0);
	if (!validate_syntax(buf, shell))
		return (0);
	return (1);
}

int	is_whitespace_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_iswhitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	init_valid_line(char **line, t_minishell *shell)
{
	if (ft_strlen(*line) == 0 || is_whitespace_string(*line)
		|| !validate_command(*line, shell))
		return (0);
	return (1);
}
