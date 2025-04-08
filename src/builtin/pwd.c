/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:16:10 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/04 15:14:45 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd_cmd(t_minishell *minishell)
{
	char	*pwd;

	pwd = getenv_value(minishell, "PWD", minishell->env_list);
	if (pwd)
	{
		ft_printf("%s\n", pwd);
		return ;
	}
	else
	{
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			ft_printf("%s\n", pwd);
			free(pwd);
		}
		else
		{
			perror("pwd");
			minishell->exit = 1;
		}
	}
	minishell->exit = 0;
}
