/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 09:37:10 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/02 16:43:06 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_invalid_pipe_syntax(char **ps, char *es, int *exit_status)
{
	if (find_token(ps, es, "|"))
	{
		ft_printf_fd(STDERR_FILENO,
			"minishell: syntax error near unexpected token `|'\n");
		*exit_status = 258;
		return (1);
	}
	return (0);
}

int	validate_redirection(char **ps, char *es, int *exit_status)
{
	char	*q;
	char	*eq;
	int		tok;

	tok = get_next_token(ps, es, &q, &eq);
	if (tok == '\0')
	{
		ft_printf_fd(STDERR_FILENO,
			"minishell: syntax error near unexpected token `newline'\n");
		*exit_status = 258;
		return (0);
	}
	else if (tok != 'a')
	{
		*eq = '\0';
		ft_printf_fd(STDERR_FILENO,
			"minishell: syntax error near unexpected token `%s'\n", q);
		*exit_status = 258;
		return (0);
	}
	return (1);
}

//haandle the end pipe
int	validate_pipe(char **ps, char *es, int *exit_status)
{
	int	tok;

	tok = get_next_token(ps, es, 0, 0);
	if (tok == '|' || tok == '\0')
	{
		ft_printf_fd(STDERR_FILENO,
			"minishell: syntax error near unexpected token `|'\n");
		*exit_status = 258;
		return (0);
	}
	else if (tok == '>' || tok == '<' || tok == '+' || tok == '%')
	{
		if (!validate_redirection(ps, es, exit_status))
			return (0);
	}
	return (1);
}

int	validate_syntax(char *line_buf, t_minishell *shell)
{
	char	*ps;
	char	*es;
	int		tok;

	ps = line_buf;
	es = ps + ft_strlen(line_buf);
	if (check_invalid_pipe_syntax(&ps, es, &shell->exit))
		return (0);
	while (!find_token(&ps, es, "\0"))
	{
		tok = get_next_token(&ps, es, 0, 0);
		if (tok == '>' || tok == '<' || tok == '+' || tok == '%')
		{
			if (!validate_redirection(&ps, es, &shell->exit))
				return (0);
		}
		else if (tok == '|')
		{
			if (!validate_pipe(&ps, es, &shell->exit))
				return (0);
		}
		else if (tok == '\0')
			break ;
	}
	return (1);
}
