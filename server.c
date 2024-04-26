/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamir <mamir@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 21:25:55 by mamir             #+#    #+#             */
/*   Updated: 2024/04/25 17:02:38 by mamir            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_data = {.bit = 0, .index = 0};

void	signal_handler(int signum)
{
	if (signum == SIGUSR1)
		g_data.bit |= 1;
	g_data.index++;
	if (g_data.index == 8)
	{
		if (g_data.bit == '\0')
			write(1, "\n", 2);
		write(1, &g_data.bit, 1);
		g_data.index = 0;
		g_data.bit = 0;
	}
	g_data.bit <<= 1;
}

int	main(int ac, char **av)
{
	pid_t	pid;

	(void)av;
	if (ac != 1)
	{
		write(2, "BAD ENTRY!\n", 12);
		exit(1);
	}
	pid = getpid();
	ft_printf("PID: %d\n", pid);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
	{
		pause();
	}
	return (0);
}
