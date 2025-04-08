/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:45:43 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/02 16:30:00 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_escaped(char *s, int pos)
{
	int	n;

	n = 0;
	while (pos >= 0 && s[pos] == '\\')
	{
		n++;
		pos--;
	}
	return (n % 2);
}

int	in_bracket(char *s, int pos)
{
	int	bracket1;
	int	bracket2;
	int	i;

	bracket1 = 0;
	bracket2 = 0;
	i = 0;
	while (i <= pos)
	{
		if (s[i] == '\"' && (i == 0 || !is_escaped(s, i - 1))
			&& bracket2 % 2 == 0)
			bracket1++;
		if (s[i] == '\'' && (i == 0 || bracket2 % 2 != 0
				|| !is_escaped(s, i - 1))
			&& bracket1 % 2 == 0)
			bracket2++;
		i++;
	}
	if (bracket1 % 2 != 0 || bracket2 % 2 != 0)
		return (1);
	return (0);
}

int	is_only_digit(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_char_str(char c, char *str)
{
	if (ft_is_in_stri(c, str) >= 0)
		return (1);
	return (0);
}

char	*supp_newline(t_minishell *minishell, char *src)
{
	int		i;
	int		j;
	char	*dest;

	if (!src)
		return (NULL);
	if (ft_is_in_stri('\n', src) == -1)
		return (src);
	i = 0;
	j = 0;
	dest = (char *)ft_calloc(1, ft_strlen(src));
	if (!dest)
		free_and_exit(minishell, 1);
	while (src[i])
	{
		if (src[i] != '\n')
		{
			dest[j] = src[i];
			j++;
		}
		i++;
	}
	dest[j] = '\0';
	return (dest);
}
