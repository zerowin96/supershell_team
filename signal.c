/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:41:32 by yeham             #+#    #+#             */
/*   Updated: 2023/02/02 17:27:00 by minsulee         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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

void	heredoc_signal(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\n");
	exit(130);
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

void	heredoc_handle_signal(void)
{
	struct sigaction	new;

	new.sa_flags = 0;
	sigemptyset(&new.sa_mask);
	new.__sigaction_u.__sa_handler = heredoc_signal;
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