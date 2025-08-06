/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-06 10:57:53 by dtimofee          #+#    #+#             */
/*   Updated: 2025-08-06 10:57:53 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenisation.h"
#include "Libft/libft.h"


char	*expand_variable(char *start, char **envp, int last_exit_code)
{
    char	*var_name;
    char	*expanded_value;
    size_t	var_len;

    if (*start == '?') // Обработка $?
    {
        expanded_value = ft_itoa(last_exit_code);
        return (expanded_value);
    }
    else // Обработка $VAR
    {
        var_len = 0;
        while (start[var_len] && (ft_isalnum(start[var_len]) || start[var_len] == '_'))
            var_len++;
        var_name = ft_substr(start, 0, var_len);
		printf("%s - var_name\n", var_name);
		fflush(0);
        expanded_value = get_env_value(var_name, envp); // Функция для получения значения переменной окружения
		printf("%s - expanded_value\n", expanded_value);
		fflush(0);
		free(var_name);
        return (expanded_value);
    }
}
