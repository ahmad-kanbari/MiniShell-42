/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:15:27 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/04 14:56:01 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	change_to_home_directory(t_minishell *minishell)
{
	char	*home_dir;

	home_dir = getenv_value(minishell, "HOME", minishell->env_list);
	if (home_dir)
	{
		if (chdir(home_dir) != 0)
		{
			perror("cd");
			minishell->exit = 1;
		}
	}
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		minishell->exit = 1;
	}
}

static	void	cd_oldpwd_check(t_minishell *minishell, t_cmd *cmd)
{
	if (chdir(getenv_value(minishell, "OLDPWD", minishell->env_list)) != 0)
	{
		ft_printf_fd(2, "minishell: cd: OLDPWD not set\n");
		minishell->exit = 1;
	}
	else
	{
		ft_printf("%s\n", getenv_value(minishell, \
			"OLDPWD", minishell->env_list));
		edit_pwd(minishell, cmd);
	}
}

static void	cd_path_check(t_cmd *cmd, t_minishell *minishell)
{
	char	*path;

	path = ft_strjoin(getenv_value(minishell, "HOME", \
		minishell->env_list), cmd->args->word + 1);
	if (chdir(path) != 0)
	{
		ft_printf_fd(2, "minishell: cd: %s: No such file or directory\n", path);
		minishell->exit = 1;
	}
	else
		edit_pwd(minishell, cmd);
	free(path);
}

void	cd_cmd(t_minishell *minishell, t_cmd *cmd)
{
	t_token	*args;

	args = cmd->args;
	if (!args)
	{
		change_to_home_directory(minishell);
		edit_pwd(minishell, cmd);
		return ;
	}
	if (ft_ifstrequal(args->word, "-"))
		cd_oldpwd_check(minishell, cmd);
	else if (args->word[0] == '~')
		cd_path_check(cmd, minishell);
	else
	{
		if (chdir(args->word))
		{
			ft_printf_fd(2, "minishell: cd: %s: \
				No such file or directory\n", args->word);
			minishell->exit = 1;
			return ;
		}
		edit_pwd(minishell, cmd);
		minishell->exit = 0;
	}
}
