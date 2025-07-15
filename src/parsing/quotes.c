/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-30 12:27:35 by dtimofee          #+#    #+#             */
/*   Updated: 2025-06-30 12:27:35 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenisation.h"
#include "../../incl/parsing.h"

//we need to check if the string has quotes and if so, we need to remove them
//the text inside doubblle quotes we need to check for $ - expansion
// // searching for single quotes and double quotes, if both == NULL -> copy the string

// char	*check_quotes(char *str)
// {
// 	char	*new_str;
// 	char	*start;
// 	char	*single_quote;
// 	char	*double_quote;
// 	int		current_len;

// 	current_len = 0;
// 	new_str = malloc(ft_strlen(str) + 1);
// 	if (!new_str)
// 		return (NULL);
// 	start = str;
// 	while (*start)
// 	{
// 		if(*start == '\'')
// 		{
// 			//should we copy here the text which was before we found the single quote?
// 			single_quote = start + 1;
// 			while (*single_quote && *single_quote != '\'')
// 				single_quote++;
// 			//here copy part from start to single_quote
// 		}
// 	}
// }
