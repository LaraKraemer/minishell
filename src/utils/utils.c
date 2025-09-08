/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:25:14 by lkramer           #+#    #+#             */
/*   Updated: 2025/09/05 16:56:52 by 123              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	print_banner(void)
{
	printf(".######..######...####...######...####...##..##..######..##......##.....\n"
		   "...##....##......##........##....##......##..##..##......##......##.....\n"
		   "...##....####.....####.....##.....####...######..####....##......##.....\n"
		   "...##....##..........##....##........##..##..##..##......##......##.....\n"
		   "...##....######...####.....##.....####...##..##..######..######..######.\n"
		   "........................................................................\n");
}

void	free_if_error(char *input, t_token **first_token)
{
	free(input);
	ms_lstclear(first_token);
}

void	free_resources(char *input, t_command *cmds, int count, t_token **first_token)
{
	free_if_error(input, first_token);
	free_commands(cmds, count);
}

char	*ft_strjoin2(const char *s1, const char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	result = malloc(i + j + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
	return (result);
}

void	free_cmds_array_env(t_command *cmds_array, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		free_array(cmds_array[i].env);
		i++;
	}
}

void	handle_heredoc_sigs(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}
