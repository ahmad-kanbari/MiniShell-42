/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akanbari <akanbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:36:39 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/02 17:33:42 by akanbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	split_utils(int i, char *str, char *splt, int sign)
{
	if (sign == 1 && is_char_str(str[i], splt) && !is_char_str(str[i + 1], splt)
		&& !in_bracket(str, i) && !is_escaped(str, i - 1))
		return (1);
	else if (!sign && is_char_str(str[i], splt) && i > 0
		&& is_char_str(str[i - 1], splt) && !in_bracket(str, i)
		&& !is_escaped(str, i - 1))
		return (1);
	else if (sign == 2 && is_char_str(str[i], splt)
		&& i > 0 && is_char_str(str[i - 1], splt) && !in_bracket(str, i)
		&& !is_escaped(str, i - 1))
		return (1);
	else if (sign == 3 && is_char_str(str[i], splt) && !in_bracket(str, i)
		&& !is_escaped(str, i - 1))
		return (1);
	return (0);
}

/*
	it will check of the
	validity of the token
	create t_token node 
	for it, it will return 0 if the command
	does not contain special character, so the split_tokens
	 function skip this iteration.
	or it will create a t_token node that hs special character 
	and return 1 so splt_tokens function
	complete its while loop
*/
int	split_tokens2(t_minishell *minishell, char *str, int *i,
			t_token **begin)
{
	if (is_char_str(str[*i], " \t") && !in_bracket(str, *i)
		&& !is_escaped(str, *i - 1))
	{
		add_token_list(begin, create_token(minishell, *i));
		(*i)++;
		return (0);
	}
	if (is_char_str(str[*i], "|;<>") && !in_bracket(str, *i)
		&& !is_escaped(str, *i - 1) && *i > 0
		&& !is_char_str(str[*i - 1], "<>"))
		add_token_list(begin, create_token(minishell, *i));
	return (1);
}

void	split_tokens(t_minishell *minishell, char *str)
{
	int			i;
	t_token		**begin;

	i = 0;
	begin = &minishell->token_list;
	minishell->count = 0;
	while (str[i])
	{
		if (!split_tokens2(minishell, str, &i, begin))
			continue ;
		minishell->count++;
		if (split_utils(i, str, "|;", 3) || split_utils(i, str, ">", 1)
			|| split_utils(i, str, ">", 0) || split_utils(i, str, "<", 1)
			|| split_utils(i, str, "<", 0))
			add_token_list(begin, create_token(minishell, i + 1));
		i++;
	}
	if (i > 0)
	{
		add_token_list(&minishell->token_list, create_token(minishell, i));
		add_token_list(&minishell->token_list,
			create_arg_token(minishell, "newline", T_NEWLINE));
	}
}

int	check_error(t_token *token)
{
	if ((token->type == T_PIPE || token->type == T_SEP) && !token->prev)
		return (0);
	if (token->type == T_REDIRECT && (token->prev \
		&& token->prev->type == T_REDIRECT))
		return (0);
	if (token->type == T_NEWLINE && token->prev
		&& (token->prev->type == T_REDIRECT || token->prev->type == T_PIPE))
		return (0);
	if ((token->type == T_PIPE || token->type == T_SEP)
		&& (token->prev->type == T_PIPE || token->prev->type == T_SEP \
		|| token->prev->type == T_REDIRECT))
		return (0);
	return (1);
}

char	*iter_tokens(t_minishell *minishell)
{
	t_token	*tmp;

	tmp = minishell->token_list;
	while (tmp)
	{
		if (ft_ifstrequal(tmp->word, ">") || ft_ifstrequal(tmp->word, ">>")
			|| ft_ifstrequal(tmp->word, "<<") || ft_ifstrequal(tmp->word, "<"))
			tmp->type = T_REDIRECT;
		else if (ft_ifstrequal(tmp->word, "|"))
			tmp->type = T_PIPE;
		else if (ft_ifstrequal(tmp->word, ";"))
			tmp->type = T_SEP;
		else if (ft_ifstrequal(tmp->word, "newline") && !tmp->next)
			tmp->type = T_NEWLINE;
		else if (is_valid_env(tmp->word))
			tmp->type = T_ENV;
		else
			tmp->type = T_WORD;
		if (!check_error(tmp) && (minishell->exit == 258))
			return (tmp->word);
		tmp = tmp->next;
	}
	return (NULL);
}
