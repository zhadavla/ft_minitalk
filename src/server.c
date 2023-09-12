#include "../ft_minitalk.h"


void handler(int signum){
	if (signum == SIGUSR1)
		printf("SIGUSR1\n");
	else if (signum == SIGUSR2)
		printf("SIGUSR2\n");
	else
		printf("Error\n");
}


int main(void){
	struct sigaction sa_signal;
	int pid;

	sa_signal.sa_handler = &handler;

	sigaction(SIGUSR1, &sa_signal, NULL);
	sigaction(SIGUSR2, &sa_signal, NULL);

	pid = getpid();
	printf("pid = %d\n", pid);
	while (1)
		pause();
	return 0;
}