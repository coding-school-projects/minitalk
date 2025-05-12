/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:37:26 by pchennia          #+#    #+#             */
/*   Updated: 2024/03/12 11:41:49 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h> // for kill(), signal()
#include <unistd.h> // for usleep()
#include <stdlib.h> // for exit()

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (res * neg);
}

void	send_character(int pid, char character)
{
	int		bit;
	char	temp_char;

	bit = 8;
	temp_char = character;
	while (bit-- > 0)
	{
		temp_char = character >> bit;
		if (temp_char % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(100);
	}
}

void	is_valid_pid(int pid, char *arg)
{
	while (*arg)
	{
		if (!(*arg >= '0' && *arg <= '9'))
		{
			write(2, "\033[31mError: Invalid server PID\n", 31);
			exit (1);
		}
		arg++;
	}
	if (kill(pid, 0) != 0)
	{
		write(2, "\033[31mError: Invalid server PID\n", 31);
		exit (1);
	}
}

int	main(int argc, char *argv[])
{
	int		server_pid;
	char	*msg;
	int		i;

	if (argc != 3)
	{
		write(2, "\033[31mError: wrong format\n", 25);
		write(2, "\033[0mTry: ./client <SERVER_PID> <string_TO_SEND>\n", 49);
		return (0);
	}
	msg = argv[2];
	server_pid = ft_atoi(argv[1]);
	is_valid_pid(server_pid, argv[1]);
	i = 0;
	while (msg[i])
		send_character(server_pid, msg[i++]);
	send_character(server_pid, '\0');
	return (0);
}
