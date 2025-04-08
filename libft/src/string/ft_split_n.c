/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_n.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:17:39 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/01 22:00:43 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static size_t	count_words(char const *s, char c, int n)
{
	int		count;
	int		is_word;

	is_word = 0;
	count = 0;
	while (*s)
	{
		if (*s == c)
			is_word = 0;
		else if (is_word == 0)
		{
			is_word = 1;
			if (count <= n)
				count++;
		}
		s++;
	}
	return (count);
}

void	ft_split_populate(char **tab, char const *s, char c, int n)
{
	int		i;
	char	*key;
	char	*value;

	i = -1;
	while (s && s[++i])
	{
		if (s[i] == c)
			break ;
	}
	key = ft_substr(s, 0, i);
	if (s[i] && s[i] == c)
		i++;
	if (s && s[i])
	{
		value = ft_substr(s, i, ft_strlen(s) - i);
		tab[1] = value;
	}
	tab[0] = key;
	tab[count_words(s, c, n)] = NULL;
}

char	**ft_split_n(char const *s, char c, int n)
{
	char	**tab;
	size_t	len;

	len = count_words(s, c, n);
	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	ft_split_populate(tab, s, c, n);
	return (tab);
}
