// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   server.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/11/25 14:42:28 by akihito           #+#    #+#             */
// /*   Updated: 2021/12/05 21:32:38 by atomizaw         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include <signal.h>
#include <zconf.h>
#include "./includes/minitalk.h"

// void	response_to_client(void)
// {
// 	int	res;

// 	if (g_print_bit.bit == 1)
// 		res = kill(g_print_bit.sipid, SIGUSR1);
// 	else
// 		res = kill(g_print_bit.sipid, SIGUSR1);
// 	if (res == -1)
// 		exit (1);
// }

// static void	handler(int sig, siginfo_t *info, void *context)
// {
// 	(void)context;
// 	if (sig == SIGUSR1)
// 		g_print_bit.bit = 1;
// 	else if (sig == SIGUSR2)
// 		g_print_bit.bit = 0;
// 	g_print_bit.sipid = info->si_pid;
// }

// void	init_signal(struct sigaction *active)
// {
// 	ft_bzero(active, sizeof(struct sigaction));
// 	active->sa_flags = SA_SIGINFO;
// 	active->sa_sigaction = handler;//ここで代入した関数がpause()でシグナルを受けた時に起動する。
// 	if (sigaction(SIGUSR1, active, NULL) != 0)
// 		exit(1);
// 	if (sigaction(SIGUSR2, active, NULL) != 0)
// 		exit(1);
// }

// void	print_pid_char(void)
// {
// 	char	*pid_char;

// 	pid_char = ft_itoa(getpid());
// 	write(1, "pid: ", 5);
// 	write(1, pid_char, ft_strlen(pid_char));
// 	write(1, "\n", 1);
// 	free (pid_char);
// }

// int	main(void)
// {
// 	struct sigaction	active;
// 	char				byte;
// 	int					count;

// 	print_pid_char();
// 	init_signal(&active);
// 	byte = 0;
// 	count = 7;
// 	while (1)
// 	{
// 		pause();
// 		if (g_print_bit.bit == 0 || g_print_bit.bit == 1)
// 			byte |= (g_print_bit.bit << (count++));
// 		if (count <= 0)
// 		{
// 			write(1, &byte, 1);
// 			count = 7;
// 			byte = 0;
// 		}
// 		usleep(25);
// 		response_to_client();
// 	}
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:57:57 by tisoya            #+#    #+#             */
/*   Updated: 2021/12/05 20:47:24 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int sig, siginfo_t *info, void *context)//infoに送信元のpid
{
	(void)context;
	if (sig == SIGUSR1)
		g_bit.bit = 1;
	else if (sig == SIGUSR2)
		g_bit.bit = 0;
	g_bit.sipid = info->si_pid;//
}

void	set_signal(struct sigaction *act)
{
	ft_bzero(&*act, sizeof(struct sigaction));
	act->sa_sigaction = handler;//sigactionじゃないと第二引数を受け取ってくれない
	sigemptyset(&act->sa_mask);
	act->sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, act, NULL) != 0)//
		exit(1);
	if (sigaction(SIGUSR2, act, NULL) != 0)
		exit(1);
}

void	sig_res(void)
{
	int	rc;

	if (g_bit.bit)
		rc = kill(g_bit.sipid, SIGUSR1);//handler()第二引数送信元pid= sipid
	else
		rc = kill(g_bit.sipid, SIGUSR2);
	if (rc == -1)
		exit(1);
}

int	main(void)
{
	struct sigaction	act;//構造体宣言
	pid_t				pid;
	char				chr;
	int					count;

	pid = getpid();//pid receive
	ft_putnbr_fd(pid, 1);// print pid
	ft_putchar_fd('\n', 1);// print ¥n
	set_signal(&act); // init struct sigaction act
	count = 0;//
	chr = 0;
	while (1)
	{
		pause();//信号待ち//ここでpause()中にシグナルが来たらhandler()が呼ばれる。
		if (g_bit.bit == 0 || g_bit.bit == 1)
			chr |= (g_bit.bit << (7 - count++));// |= 論理和　
			// |0|0|0|0|0|0|0|0
			// |1|0|1|1|0|1|0|0
		if (count >= 8)//countが１bit分になったら、write()出力。
		{
			count = 0;
			ft_putchar_fd(chr, 1);//
			chr = 0;
		}
		usleep(25);
		sig_res();
	}
}
