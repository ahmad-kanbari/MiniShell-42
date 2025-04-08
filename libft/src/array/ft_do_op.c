/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:57:48 by akanbari          #+#    #+#             */
/*   Updated: 2024/01/31 22:43:10 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_do_op(char *num1, char *sign, char *num2)
{
	int	n1;
	int	n2;
	int	result;

	result = 0;
	n1 = atoi(num1);
	n2 = atoi(num2);
	if (sign[0] == '-')
		result = n1 - n2;
	else if (sign[0] == '+')
		result = n1 + n2;
	else if (sign[0] == '*')
		result = n1 * n2;
	else if (sign[0] == '/')
		result = n1 / n2;
	else if (sign[0] == '%')
		result = n1 % n2;
	else
		printf("Enter A Valid Sign");
	return (result);
}
