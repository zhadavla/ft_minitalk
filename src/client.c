#include "../ft_minitalk.h"
#include <string.h>



int main(int agrc, char **argv)
{
	int pid;
	int i;
	int j;


	pid = atoi(argv[1]);
	if (atoi(argv[2]) % 2 == 0)
		kill(pid, SIGUSR1);
	else 
		kill(pid, SIGUSR2);
	return 0;
}