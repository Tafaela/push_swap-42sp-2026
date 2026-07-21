/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * ============================================================================
 * BENCHMARK.C - Impressão do relatório de estatísticas (--bench)
 * ============================================================================
 * Quando o programa é chamado com a flag --bench, em vez de imprimir cada
 * operação (sa, pb, ra...) na tela, ele executa o algoritmo normalmente
 * (sem imprimir as operações — ver o parâmetro "print" das funções op_*
 * em operations_*.c) e, ao final, chama print_benchmark para mostrar um
 * resumo legível do que aconteceu. Repare que tudo aqui é escrito no fd 2
 * (stderr), não no fd 1 (stdout) — isso é proposital: assim, se alguém
 * redirecionar a saída padrão do programa para um arquivo ou para o
 * checker (ex: "./push_swap --bench 3 1 2 > ops.txt"), o relatório de
 * benchmark continua aparecendo na tela, sem se misturar com a lista de
 * operações.
 * ============================================================================
 */

/*
 * print_disorder: imprime o grau de desordem inicial da pilha (calculado
 * ANTES de ordenar, em disorder.c) como uma porcentagem com duas casas
 * decimais, por exemplo "37.42%". Como o projeto não pode usar printf
 * (que teria um "%.2f" pronto), a parte inteira e a parte decimal
 * precisam ser calculadas e impressas manualmente:
 *   - "whole" é a parte inteira da porcentagem: disorder (0.0 a 1.0)
 *     multiplicado por 100 e truncado para int (ex.: 0.3742 -> 37).
 *   - "frac" pega as duas primeiras casas decimais da porcentagem:
 *     multiplicamos por 10000 em vez de 100 (ganhando 2 dígitos extras
 *     de precisão) e usamos "% 100" para isolar só essas duas últimas
 *     casas (ex.: 0.3742 -> 3742 -> 3742 % 100 = 42).
 *   - "if (frac < 0) frac = -frac": proteção contra arredondamento
 *     estranho de números de ponto flutuante que poderiam gerar um
 *     resultado ligeiramente negativo nesse cálculo.
 *   - "if (frac < 10) ft_putstr_fd("0", 2)": garante o zero à esquerda
 *     quando a parte decimal é menor que 10 (ex.: para não imprimir
 *     "37.5%" quando o certo seria "37.05%").
 */
static void	print_disorder(double disorder)
{
	int	whole;
	int	frac;

	whole = (int)(disorder * 100);
	frac = (int)(disorder * 10000) % 100;
	if (frac < 0)
		frac = -frac;
	ft_putstr_fd("[bench] disorder: ", 2);
	ft_putnbr_fd(whole, 2);
	ft_putstr_fd(".", 2);
	if (frac < 10)
		ft_putstr_fd("0", 2);
	ft_putnbr_fd(frac, 2);
	ft_putstr_fd("%\n", 2);
}

/*
 * print_op_counts: imprime, em duas linhas, a contagem de cada uma das 11
 * operações possíveis. Primeira linha: sa, sb, ss, pa, pb (as operações
 * de swap e push). Segunda linha: ra, rb, rr, rra, rrb, rrr (as operações
 * de rotação). Cada valor é impresso com ft_putnbr_fd (função que
 * escreve um int diretamente no fd, ver ft_nbr.c), intercalado com texto
 * fixo via ft_putstr_fd.
 */
static void	print_op_counts(t_ps *ps)
{
	ft_putstr_fd("[bench] sa: ", 2);
	ft_putnbr_fd(ps->op_sa, 2);
	ft_putstr_fd(" sb: ", 2);
	ft_putnbr_fd(ps->op_sb, 2);
	ft_putstr_fd(" ss: ", 2);
	ft_putnbr_fd(ps->op_ss, 2);
	ft_putstr_fd(" pa: ", 2);
	ft_putnbr_fd(ps->op_pa, 2);
	ft_putstr_fd(" pb: ", 2);
	ft_putnbr_fd(ps->op_pb, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("[bench] ra: ", 2);
	ft_putnbr_fd(ps->op_ra, 2);
	ft_putstr_fd(" rb: ", 2);
	ft_putnbr_fd(ps->op_rb, 2);
	ft_putstr_fd(" rr: ", 2);
	ft_putnbr_fd(ps->op_rr, 2);
	ft_putstr_fd(" rra: ", 2);
	ft_putnbr_fd(ps->op_rra, 2);
	ft_putstr_fd(" rrb: ", 2);
	ft_putnbr_fd(ps->op_rrb, 2);
	ft_putstr_fd(" rrr: ", 2);
	ft_putnbr_fd(ps->op_rrr, 2);
	ft_putstr_fd("\n", 2);
}

/*
 * print_benchmark: função pública deste arquivo, chamada por run_sort
 * (strategy.c) quando a flag --bench está ativa. Monta o relatório
 * completo, nesta ordem:
 *   1. O grau de desordem inicial (print_disorder).
 *   2. A estratégia usada (ex: "Adaptive") e sua complexidade teórica
 *      (ex: "O(n log n)") — esses valores vêm de run_sort/sort_adaptive,
 *      que descobrem em tempo de execução qual algoritmo foi realmente
 *      escolhido.
 *   3. O total de operações executadas (ps->total_ops) — a métrica mais
 *      importante para avaliar a eficiência do algoritmo: quanto menor,
 *      melhor.
 *   4. A contagem detalhada de cada tipo de operação (print_op_counts).
 */
void	print_benchmark(t_ps *ps, double disorder, char *strategy,
			char *complexity)
{
	print_disorder(disorder);
	ft_putstr_fd("[bench] strategy: ", 2);
	ft_putstr_fd(strategy, 2);
	ft_putstr_fd(" / ", 2);
	ft_putstr_fd(complexity, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("[bench] total_ops: ", 2);
	ft_putnbr_fd(ps->total_ops, 2);
	ft_putstr_fd("\n", 2);
	print_op_counts(ps);
}
