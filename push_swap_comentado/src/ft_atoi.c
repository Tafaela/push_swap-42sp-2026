/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * FT_ATOI.C - Conversão segura de string para inteiro
 * ============================================================================
 * Diferente do atoi() da libc (que não avisa em caso de erro/overflow),
 * esta versão "safe" (segura) RETORNA um código de sucesso/erro. Ela é
 * usada em parse.c para validar cada argumento passado pelo usuário no
 * terminal: se o argumento não for um número inteiro válido, ou se ele
 * estourar os limites de um int (INT_MIN/INT_MAX), o parse é rejeitado e
 * o programa imprime "Error".
 *
 * IMPORTANTE: este código NÃO aceita espaços em branco antes do número
 * (diferente do atoi padrão da libc, que ignora espaços iniciais) — aqui,
 * o primeiro caractere já precisa ser um sinal ou dígito.
 * ============================================================================
 */

#include "push_swap.h"

/*
 * parse_sign: olha o primeiro caractere da string (str[*i]). Se for '-'
 * ou '+', consome esse caractere (avança *i em 1) e devolve o sinal
 * correspondente (-1 ou 1). Se não houver sinal explícito, assume-se
 * positivo (1) e *i permanece no início.
 * *i é passado por referência (ponteiro) porque a função precisa "andar"
 * a posição de leitura da string para quem chamou continuar de onde
 * parou.
 */
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

/*
 * parse_digits: a partir da posição "i" (já depois do sinal, se houver),
 * lê caractere por caractere e monta o número em "*n" (do tipo long, que
 * tem mais bits que int — isso é proposital, para conseguirmos detectar
 * overflow ANTES de estourar).
 *
 * Validações feitas aqui:
 *   - Se a string terminar logo em "i" sem nenhum dígito (ex: string era
 *     só "-" ou vazia), é inválida -> retorna 0.
 *   - Se aparecer qualquer caractere que não seja dígito ('0'-'9'), é
 *     inválido -> retorna 0.
 *   - A cada dígito lido, verifica se "sign * (*n)" já ultrapassou
 *     INT_MAX ou ficou abaixo de INT_MIN. Como *n é long (maior que int),
 *     essa comparação é segura e detecta o overflow antes que ele
 *     realmente aconteça no tipo int.
 * Se tudo estiver certo até o fim da string, retorna 1 (sucesso).
 */
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

/*
 * ft_atoi_safe: função pública deste arquivo, chamada por parse.c.
 * Combina parse_sign + parse_digits:
 *   1. Rejeita string nula ou vazia de cara.
 *   2. Lê o sinal (se houver).
 *   3. Lê e valida os dígitos, checando overflow.
 *   4. Se tudo passou, grava o valor final (já com o sinal aplicado) em
 *      *result (o "int *result" recebido por parâmetro é a forma de
 *      devolver DOIS valores ao mesmo tempo: o número convertido E se
 *      deu certo ou não — já que o "return" está ocupado pelo
 *      sucesso/erro).
 * Retorna 1 em caso de sucesso, 0 se a string não for um inteiro válido.
 */
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
