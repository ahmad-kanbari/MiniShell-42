/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 19:20:10 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/04 15:08:06 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	edit_pwd_helper(t_minishell *minishell, char **backup, \
	char *cwd)
{
	if (getenv_value(minishell, "PWD", minishell->env_list) && *backup)
		insert_sorted_env_node(&minishell->env_list, \
			env_new(ft_strdup("OLDPWD"), ft_strdup(*backup), 1));
	if (getenv_value(minishell, "PWD", minishell->env_list))
		insert_sorted_env_node(&minishell->env_list, env_new(ft_strdup("PWD"), \
			ft_strdup(cwd), 1));
	free(cwd);
	if (*backup)
		ft_strdel(backup);
}

void	edit_pwd(t_minishell *minishell, t_cmd *cmd)
{
	char	*backup;
	char	*cwd;
	char	*oldpwd;

	(void)cmd;
	oldpwd = getenv_value(minishell, "PWD", minishell->env_list);
	if (oldpwd)
		backup = ft_strdup(oldpwd);
	else
		backup = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_printf_fd(2, "cd: error retrieving current directory: getcwd: " \
			"cannot access parent directories: No such file or directory\n");
		cwd = ft_strjoin(oldpwd, "/..");
		minishell->exit = 127;
	}
	edit_pwd_helper(minishell, &backup, cwd);
}
