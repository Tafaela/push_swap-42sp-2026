/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * STRATEGY.C - Reconhecimento de flags e despacho para o algoritmo certo
 * ============================================================================
 * Este arquivo faz a "ponte" entre as opções de linha de comando (flags
 * como --simple, --bench) e a escolha de qual função de ordenação
 * realmente vai rodar.
 * ============================================================================
 */

#include "push_swap.h"

/*
 * is_flag: retorna 1 se "arg" é exatamente uma das flags reconhecidas
 * pelo programa (--simple, --medium, --complex, --adaptive, --bench), e 0
 * caso contrário (ou seja, é um número/argumento normal). Usada em
 * main.c (parse_flags e count_flags) para saber onde as flags terminam e
 * onde os números começam.
 */
int	is_flag(char *arg)
{
	if (ft_strcmp(arg, "--simple") == 0)
		return (1);
	if (ft_strcmp(arg, "--medium") == 0)
		return (1);
	if (ft_strcmp(arg, "--complex") == 0)
		return (1);
	if (ft_strcmp(arg, "--adaptive") == 0)
		return (1);
	if (ft_strcmp(arg, "--bench") == 0)
		return (1);
	return (0);
}

/*
 * run_sort: função central que decide QUAL algoritmo de ordenação
 * executar, baseado na string "strategy" definida em main.c (padrão:
 * "Adaptive", a menos que o usuário tenha passado --simple/--medium/
 * --complex explicitamente).
 *
 * Passos:
 *   1. Calcula o "disorder" (grau de desordem, 0.0 a 1.0) da pilha ANTES
 *      de ordenar, usando compute_disorder (disorder.c). Isso é só para
 *      fins de estatística/benchmark — não influencia o algoritmo em si.
 *   2. "name" começa como o próprio nome da estratégia recebida, e
 *      "complexity" começa com "O(n^2)" (a complexidade padrão, usada
 *      pela estratégia Simple).
 *   3. Compara "strategy" com cada opção conhecida:
 *      - "Simple"   -> chama sort_simple (para pilhas pequenas, ex: até
 *                      3 elementos).
 *      - "Medium"   -> ajusta a complexidade esperada para
 *                      "O(n*sqrt(n))" e chama sort_medium.
 *      - "Complex"  -> ajusta a complexidade esperada para "O(n log n)"
 *                      e chama sort_complex.
 *      - qualquer outro valor (inclusive o padrão "Adaptive")
 *                      -> chama sort_adaptive, que decide sozinha (por
 *                      dentro) qual sub-algoritmo usar dependendo do
 *                      tamanho da pilha, e devolve o nome/complexidade
 *                      real usados através dos ponteiros &name e
 *                      &complexity (por isso sort_adaptive recebe
 *                      "char **name" — precisa poder alterar o próprio
 *                      ponteiro "name" da função chamadora).
 *   4. Se o modo benchmark (--bench) estiver ativo, imprime as
 *      estatísticas finais (print_benchmark) em vez de deixar como saída
 *      apenas a lista de operações — a impressão das operações
 *      individuais (pa, ra, etc.) já foi feita "ao vivo" durante a
 *      execução de cada algoritmo, quando print=1 é passado para as
 *      funções op_*.
 */
void	run_sort(t_ps *ps, char *strategy, int bench)
{
	double	disorder;
	char	*name;
	char	*complexity;

	disorder = compute_disorder(ps->a, ps->size_a);
	name = strategy;
	complexity = "O(n^2)";
	if (ft_strcmp(strategy, "Simple") == 0)
		sort_simple(ps);
	else if (ft_strcmp(strategy, "Medium") == 0)
	{
		complexity = "O(n*sqrt(n))";
		sort_medium(ps);
	}
	else if (ft_strcmp(strategy, "Complex") == 0)
	{
		complexity = "O(n log n)";
		sort_complex(ps);
	}
	else
		sort_adaptive(ps, &name, &complexity);
	if (bench)
		print_benchmark(ps, disorder, name, complexity);
}
