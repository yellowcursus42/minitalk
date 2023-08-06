/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skulkamt <skulkamt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 10:43:17 by skulkamt          #+#    #+#             */
/*   Updated: 2023/08/06 10:58:31 by skulkamt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./lib/libft/libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#define SEND_INTERVAL 500

typedef struct s_state
{
	int			sent;
	int			received;
	char		*tosend;
	int			pid;
}				t_state;

static t_state	g_state;

static void	sendchar(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << i))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(SEND_INTERVAL);
		i++;
	}
	g_state.sent++;
}

static void	action(int sig)
{
	if (*(g_state.tosend))
		sendchar(g_state.pid, *(g_state.tosend)++);
	g_state.received++;
}

// handler is too busy to reach printing
int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
		return (1);
	g_state.tosend = argv[2];
	g_state.pid = ft_atoi(argv[1]);
	signal(SIGUSR1, action);
	sendchar(g_state.pid, *(g_state.tosend)++);
	ft_putnbr_fd(g_state.received, 1);
	ft_putchar_fd(':', 1);
	ft_putnbr_fd(g_state.sent, 1);
	ft_putchar_fd('\n', 1);
	if (g_state.sent != g_state.received && *(g_state.tosend))
	{
		ft_putstr_fd("COM broken", 1);
		return (1);
	}
	return (0);
}
