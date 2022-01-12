/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvintila <lvintila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 17:57:54 by lvintila          #+#    #+#             */
/*   Updated: 2022/01/09 12:56:57 by lvintila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/myshell.h"


char **split_line(char *line)
{
	int buffsize;
	int pos;
	char **tokens;
	char *token;


	buffsize = TK_BUFF_SIZE;
	tokens = malloc(buffsize * sizeof(char*));
	if (!tokens)
	{
		fprintf(stderr, "%s($ ): Allocation error%s\n", RED, RESET);	
		exit(EXIT_FAILURE);
	}
	token = strtok(line, TOK_DELIM);
	pos = 0;
	while (token != NULL)
	{
		tokens[pos] = token;
		pos++;
		if (pos >= buffsize)
		{
			buffsize += TK_BUFF_SIZE;
			tokens = realloc(tokens, buffsize*sizeof(char*));
			if (!tokens)
			{
				fprintf(stderr, "%s($ ): Allocation error%s\n", RED, RESET);
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOK_DELIM);
	}
	tokens[pos] = NULL;
	return (tokens);
}

char *trim_ws(char *str)
{
	char *end;
	while (ft_isspace((unsigned char) *str))
		str++;
	if (*str == 0)
		return str;
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace((unsigned char) *end))
		end--;
	*(end + 1) = 0;
	return (str);
}

char **split_pipes(char *input)
{
	char *ptr;
	char **str;
	int i;
	
	str = malloc(1024 * sizeof(char *));
	ptr = strtok(input, "|");
	i = 0;
	while (ptr != NULL)
	{
		
		str[i] = trim_ws(ptr);
		i++;
		ptr = strtok(NULL, "| ");
	}
	str[i] = NULL;
	i = 0;
	while(str[i] != NULL)
	{
		printf("%s\n", str[i]);
		i++;
	}
	return (str);
}