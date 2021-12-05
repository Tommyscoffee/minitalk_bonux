#include <signal.h>
#include <zconf.h>
#include "libft.h"
#include "./includes/minitalk.h"

void	handler(int sig)
{
	(void)sig;
	return ;
}

void	usage(void)
{
	write(1, "usage: [./client] [pid] [message].", 33);
	exit(0);
}

void	init_signal(struct sigaction *active)
{
	ft_bzero(active, sizeof(struct sigaction));
	active->sa_flags = SA_SIGINFO;
	active->sa_handler = handler;//ここで代入した関数がpause()でシグナルを受けた時に起動する。
	if (sigaction(SIGUSR1, active, NULL) != 0)
		exit(1);
	if (sigaction(SIGUSR2, active, NULL) != 0)
		exit(1);
}

void	send_char(int pid_int, unsigned char byte)
{
	uint8_t		counter;//8bitの符号なし整数型　、環境によっては１バイトが8bit出ないところもある
	// 0|1|0|0|0|0|

				//char   1|0|1|0|1|1| = 'f'
	counter = 1 << 6;
	while (counter)
	{
		if (byte & counter)
		{
			if (kill(pid_int, SIGUSR1) == -1)
				error("bad pid¥n");
		}
		else
		{
			if (kill(pid_int, SIGUSR2) == -1)
				error("bad pid¥n");
		}
		counter >>= 1;
		usleep(600);
	}
}

void	main_handler(char *pid_char, char *message)
{
	pid_t				pid_int;

	pid_int = ft_atoi(pid_char);
	if (pid_int == 0 | pid_int == -1)
		exit(1);
	while (*message)
	{
		send_char(pid_int, *message);
		message++;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	active;

	if (argc != 3)
		usage();
	init_signal(&active);
	// signal(SIGUSR1, success);//signal()は移植性が低いので非推奨 sa_sigactionを使う。
	main_handler(argv[1], argv[2]);
	return (0);
}
