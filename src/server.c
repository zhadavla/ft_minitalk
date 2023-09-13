#include "../ft_minitalk.h"

char		*text = NULL;

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

void	join_text(char c, siginfo_t *info)
{
	char	copy_c[2];

	copy_c[0] = c;
	copy_c[1] = '\0';
	if (text)
		text = ft_strjoin(text, copy_c);
	else if (!text)
		text = ft_strdup(copy_c);
}

void	handler(int signum, siginfo_t *info, void *context)
{
	static int	counter;
	static char	current_bit;
	
	if (signum == SIGUSR1)
	{
		current_bit += ft_pow_of_two(counter);
		counter++;
	}
	else if (signum == SIGUSR2)
		counter++;
	else if (signum == SIGINT)
	{
		free(text);
		text = NULL;
		printf("You terminated the server!\n");
		exit(0);
	}
	if (counter == 8)
	{
		if (current_bit == 0)
		{
			printf("%s\n", text);
			free(text);
			text = NULL;
			kill(info->si_pid, SIGUSR1);
		}
		join_text(current_bit, info);
		counter = 0;
		current_bit = 0;
	}
	kill(info->si_pid, SIGUSR2);
	usleep(5);
}

int	main(void)
{
	struct sigaction sa_signal;
	int				pid;

	sigemptyset(&sa_signal.sa_mask);
	sa_signal.sa_flags = SA_SIGINFO | SA_RESTART;
	sa_signal.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	sigaction(SIGINT, &sa_signal, NULL);

	pid = getpid();
	printf("pid = %d\n", pid);
	while (1)
		sleep(1);
	return (0);
}
