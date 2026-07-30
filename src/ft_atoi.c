/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramos <bramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 00:39:28 by bramos            #+#    #+#             */
/*   Updated: 2026/07/11 00:39:29 by bramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	parse_sign(char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	parse_digits(char *str, int i, int sign, long *n)
{
	*n = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		*n = *n * 10 + (str[i] - '0');
		if (sign * (*n) > (long)INT_MAX || sign * (*n) < (long)INT_MIN)
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi_safe(char *str, int *result)
{
	long	n;
	int		sign;
	int		i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	sign = parse_sign(str, &i);
	if (!parse_digits(str, i, sign, &n))
		return (0);
	*result = (int)(sign * n);
	return (1);
}
