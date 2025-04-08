/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:43:52 by akanbari          #+#    #+#             */
/*   Updated: 2024/02/01 16:13:27 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static long	long	ft_atol_helper(const char *str, t_llint result, \
		int *reverse, int *i);

long long int	ft_atol(const char *str)
{
	int		i;
	int		reverse;
	t_llint	result;

	result = 0;
	i = 0;
	reverse = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ' )
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			reverse *= -1;
		i++;
	}
	result = 0;
	result = ft_atol_helper(str, result, &reverse, &i);
	return (result);
}

static long	long	ft_atol_helper(const char *str, t_llint result, \
	int *reverse, int *i)
{
	int	num;

	num = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		num = str[(*i)++] - '0';
		if (result > ((LLONG_MAX - num) / 10))
			return (-1);
		if ((result * -1) < ((LLONG_MIN + num) / 10))
			return (0);
		result = result * 10 + num;
	}
	return ((result) * (*reverse));
}
