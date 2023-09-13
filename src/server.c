/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:50:46 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/13 17:00:25 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minitalk.h"

char	*g_text = NULL;

static int	ft_pow_of_two(int exp)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (i < exp)
	{
		res *= 2;
		i++;
	}
	return (res);
}

void	join_g_text(char c)
{
	char	copy_c[2];

	copy_c[0] = c;
	copy_c[1] = '\0';
	if (g_text)
		g_text = ft_strjoin(g_text, copy_c);
	else if (!g_text)
		g_text = ft_strdup(copy_c);
}

void	handle_last_bit(int *counter, char *current_bit, siginfo_t *info)
{
	if (*current_bit == 0)
	{
		ft_printf("%s\n", g_text);
		free(g_text);
		g_text = NULL;
		kill(info->si_pid, SIGUSR1);
	}
	join_g_text(*current_bit);
	*counter = 0;
	*current_bit = 0;
}

void	handler(int signum, siginfo_t *info, void *cong_text)
{
	static int	counter;
	static char	current_bit;

	(void)cong_text;
	if (signum == SIGUSR1)
	{
		current_bit += ft_pow_of_two(counter);
		counter++;
	}
	else if (signum == SIGUSR2)
		counter++;
	else if (signum == SIGINT)
	{
		free(g_text);
		g_text = NULL;
		ft_printf("You terminated the server!\n");
		exit(0);
	}
	if (counter == 8)
		handle_last_bit(&counter, &current_bit, info);
	kill(info->si_pid, SIGUSR2);
	usleep(5);
}

int	main(void)
{
	struct sigaction	sa_signal;
	int					pid;

	sigemptyset(&sa_signal.sa_mask);
	sa_signal.sa_flags = SA_SIGINFO | SA_RESTART;
	sa_signal.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	sigaction(SIGINT, &sa_signal, NULL);
	pid = getpid();
	ft_printf("pid = %d\n", pid);
	while (1)
		sleep(1);
	return (0);
}
