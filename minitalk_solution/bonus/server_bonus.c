/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:38:45 by pchennia          #+#    #+#             */
/*   Updated: 2024/03/12 11:39:19 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h> // for sigaction()
#include <unistd.h> // for pause()

void	ft_putnbr(int num)
{
	char	c;

	if (num > 9)
	{
		ft_putnbr(num / 10);
		num = num % 10;
	}
	if (num <= 9)
	{
		c = (('0' + num));
		write(1, &c, 1);
	}
}

void	msg_handler(int signal, siginfo_t *info, void *s)
{
	static int	bit_index;
	static char	current_char;

	(void) s;
	if (signal == SIGUSR1)
		current_char = current_char | 1;
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == '\0')
		{
			write(1, "\n", 1);
			kill(info->si_pid, SIGUSR1);
		}
		else
			write(1, &current_char, 1);
		bit_index = 0;
		current_char = 0;
	}
	else
		current_char = current_char << 1;
}

int	main(void)
{
	struct sigaction	action;

	write(1, "Welcome To Poonkodi's Server_bonus!\n", 36);
	write(1, "My Server_bonus PID : ", 22);
	ft_putnbr(getpid());
	write(1, "\nServer_bonus Started.\nWaiting for a message...\n", 54);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = &msg_handler;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
	return (0);
}
