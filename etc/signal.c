/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:41:32 by yeham             #+#    #+#             */
/*   Updated: 2023/02/03 14:58:27 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"
#include <signal.h>
#include <sys/signal.h>

void	ft_signal(int signum)
{
	if (signum != SIGINT)
		return ;
	if (rl_on_new_line() == -1)
		exit(1);
	printf("\n");
	rl_replace_line("", 1);
	rl_redisplay();
}

void	child_signal(int signum)
{
	if (signum != SIGQUIT)
		return ;
	if (rl_on_new_line() == -1)
		exit(1);
	printf("\n");
	rl_replace_line("", 1);
	rl_redisplay();
}

void	handle_signal(void)
{
	struct sigaction	new;

	new.sa_flags = 0;
	sigemptyset(&new.sa_mask);
	new.__sigaction_u.__sa_handler = ft_signal;
	sigaction(SIGINT, &new, 0);
	new.__sigaction_u.__sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &new, 0);
}

void	parent_handle_signal(void)
{
	struct sigaction	new;

	new.sa_flags = 0;
	sigemptyset(&new.sa_mask);
	new.__sigaction_u.__sa_handler = SIG_IGN;
	sigaction(SIGINT, &new, 0);
	new.__sigaction_u.__sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &new, 0);
}

void	child_handle_signal(void)
{
	struct sigaction	new;

	new.sa_flags = 0;
	sigemptyset(&new.sa_mask);
	new.__sigaction_u.__sa_handler = ft_signal;
	sigaction(SIGINT, &new, 0);
	new.__sigaction_u.__sa_handler = child_signal;
	sigaction(SIGQUIT, &new, 0);
}
