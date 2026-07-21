/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr.c                                           :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * FT_NBR.C - Imprime um número inteiro diretamente em um file descriptor
 * ============================================================================
 * Função clássica do libft, reimplementada aqui porque o projeto não pode
 * usar printf. É usada, por exemplo, pelo benchmark.c para imprimir
 * estatísticas numéricas na tela.
 * ============================================================================
 */

#include "push_swap.h"

/*
 * ft_putnbr_fd: escreve o número "n" (dígito por dígito) no file
 * descriptor "fd" (1 = stdout/tela, 2 = stderr).
 *
 * Por que usar "long nb" em vez de trabalhar direto com "int n"?
 * Porque o menor valor possível de um int (INT_MIN, ex: -2147483648) não
 * tem um "positivo correspondente" que caiba em int (o int positivo
 * máximo é 2147483647, um a menos). Convertendo para long antes de
 * inverter o sinal (nb = -nb), evitamos esse overflow.
 *
 * Lógica:
 *   1. Se o número é negativo, imprime o sinal "-" e trabalha com o valor
 *      positivo a partir daqui.
 *   2. Se o número tem mais de um dígito (nb >= 10), a função chama a SI
 *      MESMA (recursão) para imprimir primeiro os dígitos mais à
 *      esquerda (nb / 10 remove o último dígito). Isso garante que os
 *      dígitos saiam na ordem correta (da esquerda para a direita).
 *   3. Depois da chamada recursiva (ou direto, se for um único dígito),
 *      imprime o ÚLTIMO dígito (nb % 10), convertendo o dígito numérico
 *      para o caractere correspondente somando o código ASCII de '0'.
 *
 * Exemplo com n = 123:
 *   ft_putnbr_fd(123) -> nb=123, nb>=10, chama ft_putnbr_fd(12)
 *     ft_putnbr_fd(12) -> nb=12, nb>=10, chama ft_putnbr_fd(1)
 *       ft_putnbr_fd(1) -> nb=1, nb<10, imprime '1'
 *     volta e imprime '2'
 *   volta e imprime '3'
 *   Resultado impresso: "123"
 */
void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	c;

	nb = (long)n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr_fd((int)(nb / 10), fd);
	c = (char)('0' + nb % 10);
	write(fd, &c, 1);
}
