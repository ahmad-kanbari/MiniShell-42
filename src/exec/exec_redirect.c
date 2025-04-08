/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 19:11:10 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/04 13:33:52 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	remove_util(t_token **begin, t_token **next)
{
	*next = (*begin)->next;
	free_redirect(*begin);
}

t_token	*remove_redirect(t_token *args, t_token **begin)
{
	t_token	*tmp;
	t_token	*next;

	tmp = *begin;
	if (*begin == args)
	{
		remove_util(begin, &next);
		*begin = next;
		if (next != NULL)
			next->prev = NULL;
		return (next);
	}
	while (tmp)
	{
		if (tmp == args && tmp->prev)
		{
			next = tmp->next;
			tmp->prev->next = next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			return (free_redirect(args), next);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

//this will open a file for me and check if there
// is any open file and close them
//and remove the redirect token and file name
// token after the redirectl
//and return the opened file, so i can set
// it to them cmd->out or cmd->in
int	create_redirect2(t_minishell *minishell, t_cmd *cmd, t_token **args,
				int flags)
{
	int	fd;

	fd = -1;
	fd = open((*args)->next->word, flags, 0644);
	if (fd < 0)
	{
		ft_printf_fd(2, "minishell: %s: %s\n", (*args)->next->word,
			strerror(errno));
		minishell->exit = 1;
		minishell->exit = 1;
	}
	if ((ft_ifstrequal((*args)->word, ">")
			|| (ft_ifstrequal((*args)->word, ">>"))) && cmd->out)
		close(cmd->out);
	if (ft_ifstrequal((*args)->word, "<") && cmd->in)
		close(cmd->in);
	*args = remove_redirect(*args, &cmd->args);
	*args = remove_redirect(*args, &cmd->args);
	return (fd);
}

void	process_heredoc(t_minishell *minishell, t_cmd *cmd, t_token **args)
{
	g_exit_status = IN_HERE_DOC;
	set_signal_handler_heredoc(minishell);
	ft_heredoc(minishell, args, cmd);
	*args = remove_redirect(*args, &cmd->args);
	*args = remove_redirect(*args, &cmd->args);
}

// cat >file.txt  >file2.txt >>file3.txt
//changing the cmd out will let the append and output go only to the last file
//not the first file .
void	create_redirect(t_minishell *minishell, t_cmd *cmd)
{
	t_token	*args;

	args = cmd->args;
	while (args && args->next)
	{
		if (ft_ifstrequal(args->word, ">") && args->type == T_REDIRECT
			&& cmd->out != -1 && cmd->in != -1)
			cmd->out = create_redirect2(minishell, cmd, &args,
					O_TRUNC | O_RDWR | O_CREAT);
		else if (ft_ifstrequal(args->word, ">>") && args->type == T_REDIRECT
			&& cmd->out != -1 && cmd->in != -1)
			cmd->out = create_redirect2(minishell, cmd, &args,
					O_APPEND | O_RDWR | O_CREAT);
		else if (ft_ifstrequal(args->word, "<") && args->type == T_REDIRECT
			&& cmd->in != -1)
			cmd->in = create_redirect2(minishell, cmd, &args, O_RDONLY);
		else if (ft_ifstrequal(args->word, "<<") && args->type == T_REDIRECT)
			process_heredoc(minishell, cmd, &args);
		else
			args = args->next;
	}
}
