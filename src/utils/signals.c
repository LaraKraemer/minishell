/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:04:28 by lkramer           #+#    #+#             */
/*   Updated: 2025/09/02 14:29:41 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "../../incl/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	g_signal_received = SIGINT;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	setup_interactive_sigs(void)
{
	struct sigaction	sa_int;

    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_int, NULL);
    signal(SIGQUIT, SIG_IGN);
}

void	setup_child_sigs(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_parent_sigs(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_heredoc_sigs(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}