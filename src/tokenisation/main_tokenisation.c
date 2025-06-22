/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:38:57 by dtimofee          #+#    #+#             */
/*   Updated: 2025/06/02 17:20:07 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenisation.h"

int	get_tokens(char *input, t_token **first_token)
{
	t_token			*current_token;
	t_token_type	type;
	char			*value;

	while (*input)
	{
		skip_delimiter(&input);
		if (!*input)
			return (1);
		type = determine_type(input, input + 1);
		value = determine_value(type, &input);
		if (!value)
			return (error_input("Syntax error", 1));
		if (*first_token == NULL)
		{
			*first_token = ms_lstnew(type, value);
			current_token = *first_token;
		}
		else
		{
			current_token = ms_lstnew(type, value);
			ms_lstadd_back(first_token, current_token);
		}
	}
	return (0);
}

