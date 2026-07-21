/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * FT_STR.C - Funções básicas de string (reimplementação estilo libft)
 * ============================================================================
 * O projeto push_swap não permite usar funções da libc como printf,
 * strlen, strcmp etc. Este arquivo reimplementa as poucas que o programa
 * precisa: escrever string em um fd, medir o tamanho de uma string e
 * comparar duas strings.
 * ============================================================================
 */

#include "push_swap.h"

/*
 * ft_putstr_fd: escreve a string "s" inteira no file descriptor "fd",
 * caractere por caractere, usando write() (a syscall de baixo nível que
 * printf usa por baixo dos panos). Usada para imprimir cada operação
 * (ex: "pa\n") na saída padrão durante a ordenação.
 * Se "s" for NULL, não faz nada (evita crash).
 */
void	ft_putstr_fd(char *s, int fd)
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
 * ft_strlen: conta quantos caracteres existem em "s" antes do terminador
 * nulo ('\0'). Se "s" for NULL, retorna 0 em vez de travar o programa.
 */
int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

/*
 * ft_strcmp: compara duas strings caractere a caractere enquanto forem
 * iguais e nenhuma das duas tiver terminado. Ao parar (por diferença ou
 * por uma das duas ter acabado), retorna a diferença entre os códigos
 * ASCII dos caracteres na posição em que pararam.
 *   - Retorno 0       -> as strings são idênticas.
 *   - Retorno != 0     -> as strings são diferentes (o sinal indica qual é
 *                         "maior" em ordem alfabética, mas aqui é usado
 *                         apenas para checar igualdade == 0, por exemplo
 *                         em parse_flags de main.c).
 * A conversão para "unsigned char" evita comportamento indefinido ao
 * comparar caracteres com valor negativo (char pode ser signed em alguns
 * sistemas).
 */
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
