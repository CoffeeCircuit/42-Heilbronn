#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <term.h>

char RECEIVED_BIT;

void sig1(int sig)
{
	(void)sig;
	RECEIVED_BIT = 1;
}

void sig2(int sig)
{
	(void)sig;
	RECEIVED_BIT = 0;
}


int main()
{
	printf("PID: %d\n", getpid());
	
	struct sigaction sa1 = {.sa_flags = 0, .sa_handler = &sig1};
	struct sigaction sa2 = {.sa_flags = 0, .sa_handler = &sig2};
	sigemptyset(&sa1.sa_mask);
	sigemptyset(&sa2.sa_mask);
	
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa2, NULL);
	
	char chr;
	int i;
	while (1)
	{
		i = 7;
		chr = 0;
		while (i--)
		{
			pause();
			chr |= RECEIVED_BIT << i;
		} 		
		write(1, &chr, 1);
	}
}
