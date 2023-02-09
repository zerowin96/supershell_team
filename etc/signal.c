/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:41:32 by yeham             #+#    #+#             */
/*   Updated: 2023/02/08 22:45:20 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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
