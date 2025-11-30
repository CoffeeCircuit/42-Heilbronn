#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <term.h>
#include <string.h>

void send_1(int pid)
{
	kill(pid, SIGUSR1);
}

void send_0(int pid)
{
	kill(pid, SIGUSR2);
}

void send_msg(int pid, char *msg)
{
	size_t i = 0;
	int j;
	char chr;
	while (i < strlen(msg))
	{
		chr = msg[i];
		j = 7;
		while (j--)
		{
			if ((chr & (1 << j)) >> j == 1)
				send_1(pid);
			else 
				send_0(pid);
			usleep(10);
		}
		i++;
	}
	kill(pid, SIGINT);
}

int main(int argc, char *argv[])
{
	if (argc < 3)
		return (1);
	int s_pid = (int)strtol(argv[1], NULL, 10);
	send_msg(s_pid, argv[2]);
	return (0);
}
