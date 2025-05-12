/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:37:58 by pchennia          #+#    #+#             */
/*   Updated: 2024/03/12 11:34:38 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h> // for signal()
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

void	msg_handler(int signal)
{
	static int	bit_index;
	static char	current_char;

	if (signal == SIGUSR1)
		current_char = current_char | 1;
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == '\0')
			write(1, "\n", 1);
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
	int	pid;

	pid = getpid();
	write(1, "Welcome To Poonkodi's Server!\n", 30);
	write(1, "My Server PID : ", 16);
	ft_putnbr(pid);
	write (1, "\nServer Started.\nWaiting for a message...\n", 48);
	signal(SIGUSR1, msg_handler);
	signal(SIGUSR2, msg_handler);
	while (1)
		pause();
	return (0);
}
