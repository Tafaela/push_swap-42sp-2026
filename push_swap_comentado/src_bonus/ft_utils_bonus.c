/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:  */
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
 * FT_UTILS_BONUS.C - Funções de string usadas pelo checker
 * ============================================================================
 * Versões duplicadas (com sufixo "_b") de ft_putstr_fd e ft_strcmp do
 * push_swap principal (ft_str.c) — necessárias porque o checker é
 * compilado separadamente. Note que este arquivo não duplica ft_strlen
 * porque o checker não precisa medir tamanho de strings em nenhum lugar.
 * ============================================================================
 */

/*
 * ft_putstr_fd_b: escreve a string "s" inteira no file descriptor "fd",
 * caractere por caractere. Usada para imprimir "OK\n", "KO\n" ou
 * "Error\n" no checker.
 */
void	ft_putstr_fd_b(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

/*
 * ft_strcmp_b: compara duas strings caractere a caractere, retornando 0
 * se forem idênticas. Usada para reconhecer qual operação foi lida da
 * entrada padrão (ex: comparar a linha lida com "pa", "sb", "rrr" etc,
 * em operations_bonus.c e operations_bonus2.c).
 */
int	ft_strcmp_b(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
