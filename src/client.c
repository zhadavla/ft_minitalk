/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:51:18 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/13 16:56:20 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minitalk.h"
#include <string.h>

/**
 * Sends a char to a process
 * meaning it sends 8 signals to the process
 * representing the 8 bits of the char
 * it iterates through the bits of the char
 * and sends a SIGUSR1 to the process if the bit is 1  else it sends SIGUSR2
 */
void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		usleep(1);
		if (c & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(424242);
		c = c >> 1;
		i++;
	}
}

void	send_string(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(pid, str[i]);
		i++;
	}
	if (str[i] == '\0')
		send_char(pid, '\0');
}

void	handler_client(int signum)
{
	if (signum == SIGUSR1)
		ft_printf("Message received by the server\n");
}

int	main(int argc, char **argv)
{
	int	pid;

	signal(SIGUSR1, handler_client);
	signal(SIGUSR2, handler_client);
	if (argc != 3)
	{
		ft_printf("Usage: ./client [pid] [string]\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	send_string(pid, argv[2]);
	return (0);
}
