/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:25:55 by mamir             #+#    #+#             */
/*   Updated: 2024/04/24 21:15:10 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_data	g_data = {.bit = 0, .index = 0};

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1)
		g_data.bit |= 1;
	g_data.index++;
	if (g_data.index == 8)
	{
		if (g_data.bit == '\0')
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR1);
		}
		write(1, &g_data.bit, 1);
		g_data.index = 0;
		g_data.bit = 0;
	}
	g_data.bit <<= 1;
}

int	main(int ac, char **av)
{
	pid_t				pid;
	struct sigaction	sa;

	(void)av;
	if (ac != 1)
	{
		write(2, "BAD ENTRY!\n", 12);
		exit(1);
	}
	pid = getpid();
	ft_printf("PID: %d\n", pid);
	sa.sa_sigaction = &signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
