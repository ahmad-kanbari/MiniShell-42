/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 22:22:32 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/02 16:33:44 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unlink_file(void)
{
	int	fd;

	fd = open("child_pid.tmp", O_RDONLY);
	if (fd > 0)
	{
		close(fd);
		unlink("child_pid.tmp");
	}
	fd = open("here_doc_tmp", O_RDONLY);
	if (fd > 0)
	{
		close(fd);
		unlink("here_doc_tmp");
	}
}

char	**join_args(t_minishell *minishell, t_cmd *cmd)
{
	char	**args;
	t_token	*tmp;
	int		i;

	i = 1;
	if (!cmd->cmd)
		return (NULL);
	args = (char **)ft_calloc(1, sizeof(char *)
			* (token_list_size(&cmd->args) + 2));
	if (!args)
		free_and_exit(minishell, minishell->exit);
	args[0] = ft_strdup(cmd->cmd);
	tmp = cmd->args;
	while (tmp)
	{
		args[i] = ft_strdup(tmp->word);
		tmp = tmp->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

int	is_only_ascii(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isascii(str[i]))
			return (0);
		i++;
	}
	return (1);
}
