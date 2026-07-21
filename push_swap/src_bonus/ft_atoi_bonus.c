/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static int	parse_sign_b(char *str, int *i)
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

static int	parse_digits_b(char *str, int i, int sign, long *n)
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

int	ft_atoi_safe_b(char *str, int *result)
{
	long	n;
	int		sign;
	int		i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	sign = parse_sign_b(str, &i);
	if (!parse_digits_b(str, i, sign, &n))
		return (0);
	*result = (int)(sign * n);
	return (1);
}
