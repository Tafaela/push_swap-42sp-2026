/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.c                                        :+:      :+:    :+:  */
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
 * GNL_BONUS.C - get_next_line: lê uma linha por vez de um file descriptor
 * ============================================================================
 * O checker precisa ler as operações digitadas/enviadas pelo push_swap,
 * uma linha de cada vez, da entrada padrão (fd 0). Esta é uma
 * implementação simplificada (mas funcional) do clássico exercício
 * "get_next_line" da 42 — aqui feita lendo BYTE A BYTE com read(), o que
 * é menos eficiente que a versão "com buffer" tradicional do projeto GNL,
 * mas suficiente para o uso do checker (que não precisa lidar com
 * arquivos gigantes).
 * ============================================================================
 */

#define GNL_BUF_SIZE 1024

/*
 * extend_line: quando o buffer atual ("line", com capacidade "*cap")
 * fica pequeno demais para caber mais um caractere, esta função DOBRA a
 * capacidade (*cap *= 2), aloca um novo buffer maior, copia o conteúdo já
 * lido (os primeiros "len" caracteres) para dentro dele, libera o buffer
 * antigo e retorna o novo.
 * Essa técnica (realocar dobrando de tamanho) é uma estratégia clássica
 * para evitar realocar a cada caractere — amortiza o custo de realocação
 * ao longo do tempo (crescimento geométrico em vez de linear).
 * Se o malloc do novo buffer falhar, libera o buffer antigo e retorna
 * NULL (sinal de erro/falta de memória).
 */
static char	*extend_line(char *line, int *cap, int len)
{
	char	*new_line;
	int		i;

	*cap *= 2;
	new_line = (char *)malloc(*cap);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		new_line[i] = line[i];
		i++;
	}
	free(line);
	return (new_line);
}

/*
 * read_loop: lê o file descriptor "fd" um caractere ("c") de cada vez,
 * usando read(fd, &c, 1), até encontrar uma quebra de linha ('\n') ou até
 * o read() retornar 0/negativo (fim do arquivo ou erro).
 *
 * A cada caractere lido (diferente de '\n'):
 *   - Se o buffer estiver prestes a ficar cheio (len + 1 >= *cap, ou
 *     seja, não caberia mais esse caractere MAIS o terminador '\0' no
 *     final), chama extend_line para crescer o buffer antes de continuar.
 *   - Grava o caractere na posição "len" e incrementa "len".
 *
 * Casos especiais tratados ao final do laço:
 *   - Se não foi lido NENHUM caractere (len == 0) E o read() indicou fim
 *     de arquivo/erro (ret <= 0), significa que não há mais nada para
 *     ler: libera o buffer (que ficaria vazio e inútil) e retorna NULL —
 *     esse é o sinal usado por process_lines (checker_bonus.c) para saber
 *     que deve parar de chamar get_next_line.
 *   - Caso contrário (leu pelo menos um caractere, mesmo que o arquivo
 *     tenha terminado sem quebra de linha final), fecha a string com
 *     '\0' na posição "len" e retorna a linha lida normalmente.
 */
static char	*read_loop(int fd, char *line, int *cap)
{
	char	c;
	int		len;
	int		ret;

	len = 0;
	ret = read(fd, &c, 1);
	while (ret > 0 && c != '\n')
	{
		if (len + 1 >= *cap)
			line = extend_line(line, cap, len);
		if (!line)
			return (NULL);
		line[len++] = c;
		ret = read(fd, &c, 1);
	}
	if (len == 0 && ret <= 0)
	{
		free(line);
		return (NULL);
	}
	line[len] = '\0';
	return (line);
}

/*
 * get_next_line: função pública deste arquivo. Aloca um buffer inicial
 * de GNL_BUF_SIZE (1024) bytes e delega a leitura de fato para
 * read_loop, que cresce o buffer conforme necessário.
 * Retorna a linha lida (sem o caractere '\n' no final) ou NULL quando não
 * há mais nada para ler, ou em caso de erro de alocação.
 */
char	*get_next_line(int fd)
{
	char	*line;
	int		cap;

	cap = GNL_BUF_SIZE;
	line = (char *)malloc(cap);
	if (!line)
		return (NULL);
	return (read_loop(fd, line, &cap));
}
