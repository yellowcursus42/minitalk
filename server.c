/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skulkamt <skulkamt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 10:42:43 by skulkamt          #+#    #+#             */
/*   Updated: 2023/08/06 10:42:45 by skulkamt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib/libft/libft.h"
#include <signal.h>
#include <unistd.h>

static void	handler(int sig, siginfo_t *info, void *context)
{
	static int				bit;
	pid_t					client_pid;
	static unsigned char	c;

	(void)context;
	if (info->si_pid)
		client_pid = info->si_pid;
	c |= (sig == SIGUSR2) << bit++;
	if (bit >= 8)
	{
		ft_putchar_fd(c, 1);
		kill(client_pid, SIGUSR1);
		bit = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	s_sigaction.sa_sigaction = handler;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		pause();
	return (0);
}
