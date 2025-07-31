/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:51:03 by lkramer           #+#    #+#             */
/*   Updated: 2025/07/31 14:24:46 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	error_input(char *msg, int error)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("❌ error: ", 2);
	ft_putstr_fd(RESET, 2);
	ft_putstr_fd(msg, 2);
	return (error);
}

void	print_error(char *arg, char *message)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(" ❌ ", 2);
	ft_putstr_fd(RESET, 2);
	ft_putstr_fd(message, 2);
}

void	sys_error(char *context, char *arg)
{
	ft_putstr_fd(RED " ❌ error: ", 2);
	ft_putstr_fd(context, 2);
	ft_putstr_fd(": ", 2);
	if (arg)
		ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(RESET, 2);
	perror("");
}

int	print_error_return(char *arg, char *message, int code)
{
	print_error(arg, message);
	return (code);
}
