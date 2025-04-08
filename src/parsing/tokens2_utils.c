/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 19:07:14 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/03 16:47:41 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_token_front(t_token **begin, t_token *new)
{
	if (*begin)
	{
		new->next = *begin;
		(*begin)->prev = new;
		*begin = new;
	}
	else
		*begin = new;
}

t_token	*token_split_to_list(t_minishell *shell, char **split)
{
	t_token		*new;
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (split[count])
		count++;
	new = NULL;
	while (i < count)
	{
		add_token_list(&new, create_arg_token(shell, split[i], T_WORD));
		i++;
	}
	return (new);
}

char	**args_to_array(t_minishell *minishell, t_cmd *cmd)
{
	char		**array;
	int			i;
	t_token		*tmp;

	(void)minishell;
	i = 1;
	array = ft_calloc(1, sizeof(char *) \
		* (token_list_size(&cmd->args) + 2));
	if (!array)
		free_and_exit(minishell, 1);
	array[0] = cmd->cmd;
	tmp = cmd->args;
	while (tmp)
	{
		array[i] = tmp->word;
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

//create a token, based on word and type
t_token	*create_arg_token(t_minishell *minishell, char *word, int type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!(new))
		free_and_exit(minishell, 1);
	new->word = ft_strdup(word);
	new->type = type;
	return (new);
}

//check the env variable length and if is is valid or not
//when creating the environmental variable the first character has 
//to be _ or alphabets only, the next other characters have to be alpha numeric.
//iam not sure about ?, but if it there you have to to 
//check for all environment variables
//it is not supposed to have space after the equal
int	ft_envlen(t_minishell *minishell, char *src, int i)
{
	int		count;
	char	buf[4096];

	count = 0;
	ft_bzero(buf, 4096);
	i++;
	while (src[i] && (ft_isalnum(src[i]) || \
		is_char_str(src[i], "?_")))
	{
		if (ft_isdigit(src[i]) && count == 0)
			return (0);
		buf[count] = src[i];
		if (src[i] == '?' && count == 0)
			break ;
		i = i + 1;
		count++;
	}
	if (getenv_value(minishell, buf, minishell->env_list))
		count = ft_strlen(getenv_value(minishell, buf, minishell->env_list));
	else
		count = 0;
	return (count);
}
