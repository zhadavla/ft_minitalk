#include "../ft_minitalk.h"

// int current_bit = 0;
char *text = NULL;

// void print_char(void){
// 	// printf("current bit = {%d}\n", current_bit);
// 	write(1, &current_bit, 1);
// }

// may be rewriteten as banch of if statements
static int ft_pow_of_two(int exp){
	if (exp == 0)
		return 1;
	if (exp == 1)
		return 2;
	if (exp == 2)
		return 4;
	if (exp == 3)
		return 8;
	if (exp == 4)	
		return 16;
	if (exp == 5)	
		return 32;
	if (exp == 6)
		return 64;
	if (exp == 7)
		return 128;
}

void join_text(char c, siginfo_t *info)
{
	char copy_c[2];

	copy_c[0] = c;
	copy_c[1] = '\0';
	if (text)
		text = ft_strjoin(text, copy_c);
	else if (!text)
	{
		// printf("text = {%s}\n", text);
		text = ft_strdup(copy_c);
	}
	kill(info->si_pid, SIGUSR2);
}

void handler(int signum, siginfo_t *info, void *context){
	static int counter = 0;
	static char current_bit = 0;

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
		printf("Error another signal\n");
		exit(0);
	}
	if (counter == 8){
		if (current_bit == 0){
			printf("%s\n", text);
			free(text);
			text = NULL;
			kill(info->si_pid, SIGUSR1);
		}
		join_text(current_bit, info);
		counter = 0;
		current_bit = 0;
	}
	usleep(5);
}


// int main(void){
// 	struct sigaction sa_signal;
// 	int pid;

// 	sa_signal.sa_sigaction = handler;
// 	sigemptyset(&sa_signal.sa_mask);
// 	sa_signal.sa_flags = SA_SIGINFO;
// 	sigaction(SIGUSR1, &sa_signal, NULL);
// 	sigaction(SIGUSR2, &sa_signal, NULL);

// 	pid = getpid();
// 	printf("pid = %d\n", pid);
// 	while (1)
// 		sleep(1);
// 	return 0;
// }

int main(void){
	struct sigaction sa_signal;
	int pid;

	sigemptyset(&sa_signal.sa_mask);
	sa_signal.sa_flags = SA_SIGINFO;
	sa_signal.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);
	sigaction(SIGINT, &sa_signal, NULL);

	pid = getpid();
	printf("pid = %d\n", pid);
	while (1)
		pause();
	return 0;
}