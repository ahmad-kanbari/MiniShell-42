/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:07:39 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/02 16:49:50 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_bin(t_minishell *minishell)
{
	int		i;
	char	**bin;
	char	*ban;

	i = 0;
	ban = NULL;
	ban = getenv_value(minishell, "PATH", minishell->env_list);
	bin = NULL;
	if (ban)
		bin = ft_split(ban, ':');
	while (bin && bin[i])
	{
		bin[i] = ft_strjoin_one_free(bin[i], "/");
		i++;
	}
	ft_free_split(&minishell->bin);
	minishell->bin = bin;
}

char	*get_bin(t_minishell *minishell, char *cmd)
{
	int		i;
	char	*joined_path;

	i = 0;
	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	if (!minishell->bin)
		return (ft_strjoin("./", cmd));
	while (minishell->bin && minishell->bin[i])
	{
		joined_path = ft_strjoin(minishell->bin[i], cmd);
		if (access(joined_path, F_OK) == 0)
			return (joined_path);
		ft_strdel(&joined_path);
		i++;
	}
	return (NULL);
}
