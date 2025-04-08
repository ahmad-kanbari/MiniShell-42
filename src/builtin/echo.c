/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:15:39 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/04 13:10:56 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	echo_cmd_helper(int *endl, int *i, t_token **args)
{
	while (*args && (*args)->word[0] == '-' && (*args)->word[1] == 'n')
	{
		*i = 2;
		while ((*args)->word[*i] == 'n')
			(*i)++;
		if ((*args)->word[*i] == 0)
		{
			*endl = 0;
			(*args) = (*args)->next;
		}
		else if ((*args)->word[*i] != 0)
			break ;
	}
}

void	echo_cmd(t_minishell *minishell, t_cmd *cmd)
{
	t_token		*args;
	int			endl;
	int			i;

	i = 2;
	args = cmd->args;
	endl = 1;
	echo_cmd_helper(&endl, &i, &args);
	while (args)
	{
		ft_putstr_fd(args->word, 1);
		if (args->next)
			ft_putchar_fd(' ', 1);
		args = args->next;
	}
	if (endl)
		ft_putchar_fd('\n', 1);
	minishell->exit = 0;
	minishell->exit = 0;
}
