/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeham <yeham@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:28:24 by yeham             #+#    #+#             */
/*   Updated: 2023/02/03 14:28:34 by yeham            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	heredoc_signal(int signum)
{
	if (signum != SIGINT)
		return ;
	printf("\n");
	exit(130);
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
