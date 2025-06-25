/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimofee <dtimofee@student.42berlin.de>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-06 14:50:02 by dtimofee          #+#    #+#             */
/*   Updated: 2025-06-06 14:50:02 by dtimofee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/tokenisation.h"
# include "Libft/libft.h"

int	error_input(char *msg, int error)
{
	ft_putendl_fd(msg, 2);
	return (error);
}
