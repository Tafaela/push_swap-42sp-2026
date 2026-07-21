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

/*
 * ============================================================================
 * FT_ATOI_BONUS.C - Conversão segura de string para inteiro (versão do
 * checker)
 * ============================================================================
 * É uma cópia praticamente idêntica de ft_atoi.c (do push_swap
 * principal), duplicada aqui com o sufixo "_b" porque o checker é
 * compilado como um binário INDEPENDENTE do push_swap — ele não pode
 * simplesmente "importar" as funções do outro programa, então cada
 * função utilitária precisa da sua própria cópia dentro de src_bonus/.
 * Veja os comentários completos em src/ft_atoi.c; a lógica é a mesma.
 * ============================================================================
 */

/*
 * parse_sign_b: lê um sinal opcional ('+' ou '-') no início da string,
 * avançando o índice *i se encontrar um. Retorna -1 para negativo, 1
 * para positivo/ausência de sinal.
 */
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

/*
 * parse_digits_b: lê os dígitos restantes da string e monta o valor em
 * "*n" (long, para detectar overflow com segurança antes de convertermos
 * para int). Rejeita strings vazias, com caracteres não numéricos, ou que
 * estourem os limites de um int.
 */
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

/*
 * ft_atoi_safe_b: função pública, usada por parse_bonus.c para validar e
 * converter cada argumento numérico passado ao checker. Retorna 1 em
 * caso de sucesso (gravando o valor em *result), 0 se a string não for um
 * inteiro válido.
 */
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
