/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:28:56 by akanbari          #+#    #+#             */
/*   Updated: 2024/01/31 22:42:56 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_count_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}
