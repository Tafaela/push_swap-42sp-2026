/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*   By: bramos <bramos@student.42.fr>               +#+  +:+       +#+      */
/*                                                 +#+#+#+#+#+   +#+         */
/*   Created: 2026/06/30 00:00:00 by bramos            #+#    #+#           */
/*   Updated: 2026/06/30 00:00:00 by bramos           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

/*
 * ============================================================================
 * MAIN.C - Ponto de entrada do programa push_swap
 * ============================================================================
 * Este é o arquivo que o sistema operacional executa primeiro. Sua função
 * é curta de propósito: ele apenas ORQUESTRA as etapas do programa,
 * delegando o trabalho pesado para outras funções (parse_args, run_sort,
 * etc). As etapas são:
 *   1. Ler as "flags" (opções tipo --bench, --simple) passadas no terminal.
 *   2. Fazer o parse (leitura/validação) dos números restantes.
 *   3. Se já estiver ordenado, não faz nada (não imprime nenhuma operação).
 *   4. Rodar o algoritmo de ordenação escolhido.
 *   5. Liberar (free) toda a memória alocada antes de terminar.
 * ============================================================================
 */

#include "push_swap.h"

/*
 * parse_flags: percorre os argumentos do início (argv[1], argv[2]...)
 * enquanto forem "flags" (strings que começam com "--", ver is_flag em
 * strategy.c) e configura duas saídas por meio de ponteiros:
 *   - *strategy: qual algoritmo usar depois ("Simple", "Medium", "Complex"
 *     ou "Adaptive"). O padrão, se nenhuma flag for passada, é "Adaptive"
 *     (o programa escolhe sozinho a melhor estratégia pelo tamanho da
 *     pilha).
 *   - *bench: 1 se a flag --bench foi passada (liga o modo benchmark, que
 *     imprime estatísticas ao final em vez de imprimir as operações).
 *
 * static: essa função só pode ser chamada de dentro deste próprio arquivo
 * (main.c). Isso é uma boa prática em C: funções auxiliares que não
 * precisam ser vistas por outros arquivos ficam "privadas" com static.
 */
static void	parse_flags(int argc, char **argv, char **strategy, int *bench)
{
	int	i;

	*strategy = "Adaptive";
	*bench = 0;
	i = 1;
	while (i < argc && is_flag(argv[i]))
	{
		if (ft_strcmp(argv[i], "--bench") == 0)
			*bench = 1;
		else if (ft_strcmp(argv[i], "--simple") == 0)
			*strategy = "Simple";
		else if (ft_strcmp(argv[i], "--medium") == 0)
			*strategy = "Medium";
		else if (ft_strcmp(argv[i], "--complex") == 0)
			*strategy = "Complex";
		else if (ft_strcmp(argv[i], "--adaptive") == 0)
			*strategy = "Adaptive";
		i++;
	}
}

/*
 * count_flags: faz a MESMA varredura que parse_flags (percorre enquanto
 * for flag), mas em vez de configurar strategy/bench, apenas devolve o
 * índice de argv onde as flags terminam e começam os números de verdade.
 * Ou seja: se o usuário rodou "./push_swap --bench 3 1 2", count_flags
 * retorna 2 (índice de "3" em argv), indicando "comece a ler números a
 * partir daqui".
 */
static int	count_flags(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc && is_flag(argv[i]))
		i++;
	return (i);
}

/*
 * main: função obrigatória em C, é a primeira a ser chamada quando o
 * programa roda. Recebe:
 *   argc -> quantidade de argumentos (incluindo o nome do programa)
 *   argv -> vetor de strings com os argumentos (argv[0] é o nome do
 *           programa, argv[1] em diante são os argumentos do usuário)
 */
int	main(int argc, char **argv)
{
	t_ps	ps;
	char	*strategy;
	int		bench;
	int		arg_start;

	/* Sem nenhum argumento além do nome do programa: não há o que
	 * ordenar, então termina sem erro (comportamento padrão do 42
	 * push_swap: rodar sem argumentos não deve imprimir nada). */
	if (argc < 2)
		return (0);
	/* Lê as flags (--bench, --simple, etc.) e descobre em que índice de
	 * argv os números de verdade começam. */
	parse_flags(argc, argv, &strategy, &bench);
	arg_start = count_flags(argc, argv);
	/* Se só havia flags e nenhum número depois delas, não há nada para
	 * ordenar. */
	if (arg_start >= argc)
		return (0);
	/* (t_ps){0}: inicializa TODOS os campos da struct ps com zero/NULL de
	 * uma vez só (equivalente a fazer memset(&ps, 0, sizeof(ps))). Isso é
	 * fundamental para evitar "lixo de memória" nos ponteiros a/b e nos
	 * contadores de operação antes de começarmos a preenchê-los. */
	ps = (t_ps){0};
	/* parse_args lê os números de argv[arg_start] em diante, valida (são
	 * números válidos? não há duplicados? não estouram o int?) e monta a
	 * pilha A. Se algo estiver errado, imprime "Error" na saída de erro
	 * (fd 2) e o programa termina com código de erro 1. */
	if (!parse_args(&ps, argc, argv, arg_start))
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	/* Se a pilha ficou vazia (não deveria acontecer aqui, mas é uma
	 * checagem de segurança) ou já está ordenada, não há necessidade de
	 * imprimir nenhuma operação: libera a memória e termina. */
	if (!ps.a || is_sorted(ps.a))
	{
		free_ps(&ps);
		return (0);
	}
	/* Executa de fato o algoritmo de ordenação escolhido (ou o adaptativo
	 * por padrão), imprimindo cada operação realizada (sa, pb, ra...) na
	 * saída padrão — a menos que --bench tenha sido passado, caso em que
	 * imprime estatísticas em vez das operações. */
	run_sort(&ps, strategy, bench);
	/* Libera toda a memória alocada dinamicamente (nós das pilhas A e B)
	 * antes de encerrar o programa, evitando memory leaks. */
	free_ps(&ps);
	return (0);
}
