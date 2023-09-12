#include "../ft_minitalk.h"

int current_bit = 0;

void print_char(void){
	// printf("current bit = {%d}\n", current_bit);
	write(1, &current_bit, 1);
}

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

void handler(int signum){
	static int counter = 0;

	if (signum == SIGUSR1)
	{	
		current_bit += ft_pow_of_two(counter);
		counter++;
	}
	else if (signum == SIGUSR2)
		counter++;
	if (counter == 8){
		counter = 0;
		print_char();
		current_bit = 0;
	}
	usleep(5);
	
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
		sleep(1);
	return 0;
}