/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:  */
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
 * CHECKER_BONUS.C - Ponto de entrada do programa checker (bônus)
 * ============================================================================
 * O checker é um programa SEPARADO do push_swap: ele recebe os mesmos
 * números como argumento, e depois lê da entrada padrão (stdin) uma
 * sequência de operações (uma por linha, ex: "pa", "rrb"), executa cada
 * uma sobre as pilhas A e B, e ao final informa se o resultado é válido.
 *
 * Uso típico: "./push_swap 3 1 2 | ./checker 3 1 2" — a saída do
 * push_swap (a lista de operações) é redirecionada (pipe) diretamente
 * para a entrada do checker, que confirma se aquela sequência realmente
 * ordena a pilha.
 * ============================================================================
 */

/*
 * process_lines: lê, uma a uma, todas as linhas disponíveis na entrada
 * padrão (fd 0) usando get_next_line (gnl_bonus.c), até não haver mais
 * nenhuma linha (get_next_line retorna NULL quando chega ao fim do
 * arquivo/stream).
 * Para cada linha lida, chama exec_op (operations_bonus.c) para
 * interpretar e executar a operação correspondente. Se exec_op não
 * reconhecer a operação (retornar 0 — string inválida, tipo "xyz"),
 * libera a linha e aborta imediatamente, retornando erro (0).
 * Cada linha lida é liberada (free) logo depois de usada, pois
 * get_next_line aloca memória dinamicamente a cada chamada.
 */
static int	process_lines(t_ps *ps)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		if (!exec_op(ps, line))
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(0);
	}
	return (1);
}

/*
 * main: ponto de entrada do checker.
 * Passos:
 *   1. Sem argumentos além do nome do programa, termina sem erro (não há
 *      nada para verificar).
 *   2. Inicializa as pilhas A e B como vazias (NULL).
 *   3. parse_args_b (parse_bonus.c) lê e valida os números do argv,
 *      montando a pilha A inicial. Se algo estiver errado (número
 *      inválido, duplicata), imprime "Error" e termina com código 1.
 *   4. process_lines lê e executa cada operação vinda da entrada padrão.
 *      Se alguma operação for inválida, libera tudo, imprime "Error" e
 *      termina com código 1.
 *   5. Se tudo correu bem, verifica o resultado final: a pilha A precisa
 *      estar ordenada (is_sorted_b) E a pilha B precisa estar
 *      COMPLETAMENTE VAZIA (!ps.b) — só assim a sequência de operações é
 *      considerada válida. Imprime "OK" nesse caso, ou "KO" caso
 *      contrário.
 *   6. Libera toda a memória alocada antes de terminar.
 */
int	main(int argc, char **argv)
{
	t_ps	ps;

	if (argc < 2)
		return (0);
	ps.a = NULL;
	ps.b = NULL;
	if (!parse_args_b(&ps, argc, argv))
	{
		ft_putstr_fd_b("Error\n", 2);
		return (1);
	}
	if (!process_lines(&ps))
	{
		free_stack_b(&ps.a);
		free_stack_b(&ps.b);
		ft_putstr_fd_b("Error\n", 2);
		return (1);
	}
	if (is_sorted_b(ps.a) && !ps.b)
		ft_putstr_fd_b("OK\n", 1);
	else
		ft_putstr_fd_b("KO\n", 1);
	free_stack_b(&ps.a);
	free_stack_b(&ps.b);
	return (0);
}
