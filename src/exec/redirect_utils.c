/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 20:51:21 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/02 22:39:37 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env2(void *lst)
{
	t_env	*env;

	env = lst;
	ft_strdel(&env->key);
	ft_strdel(&env->value);
	free(env);
}

void	free_redirect(t_token *tmp)
{
	ft_strdel(&tmp->word);
	free(tmp);
}

void	save_child_pid(int pid, t_minishell *shell)
{
	int	fd;

	fd = open("child_pid.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0677);
	if (fd < 0)
		free_panic_exit(shell, "open", 1);
	if (write(fd, &pid, sizeof(int)) < 0)
		free_panic_exit(shell, "write", 1);
	close(fd);
}

void	read_heredoc(t_minishell *shell, int fd, char **limiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!(line) || !ft_strcmp(*limiter, line))
			break ;
		else
		{
			if (ft_is_in_stri('$', line) > -1)
				line = replace_env(shell, line, 0);
			ft_putstr_fd(line, fd);
			ft_putchar_fd('\n', fd);
		}
		ft_strdel(&line);
	}
	close (fd);
	free(line);
	close_fds(shell->fpip, shell->spip);
}

void	ft_heredoc(t_minishell *shell, t_token **token, t_cmd *cmd)
{
	int		pid;
	char	*limiter;
	int		fd;
	int		cpid;

	pid = fork();
	if (pid == -1)
		free_panic_exit(shell, "Fork failed in heredoc\n", 1);
	if (pid == 0)
	{
		cpid = getpid();
		save_child_pid(cpid, shell);
		if (cmd->in)
			close(cmd->in);
		(*token)->next->word = handle_quotes(shell, (*token)->next->word, 0);
		limiter = (*token)->next->word;
		fd = open("here_doc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
		read_heredoc(shell, fd, &limiter);
		free_heredoc(shell, 0);
	}
	else
	{
		wait(NULL);
		cmd->in = open("here_doc_tmp", O_RDONLY);
	}
}
