/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:11:30 by dklimkin          #+#    #+#             */
/*   Updated: 2023/11/27 15:11:31 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	send_message(int server_pid, char *message)
{
	char	c;
	char	bit;
	int		i;
	int		k;

	i = 0;
	bit = 0;
	while (message[i] != '\0')
	{
		c = message[i];
		k = 7;
		while (k >= 0)
		{
			if ((c >> k) & 1)
				kill(server_pid, SIGUSR2);
			else
				kill(server_pid, SIGUSR1);
			usleep(500);
			k--;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	char				*message;
	int					server_pid;

	if (argc != 3)
	{
		ft_printf("please provide PID and a string\n");
		exit(1);
	}
	server_pid = ft_atoi(argv[1]);
	if (!server_pid)
	{
		ft_printf("please provide correct server PID\n");
		exit (1);
	}
	message = argv[2];
	ft_printf("client %d says:\n\n%s ⸜(ˆᗜˆ˵ )⸝\n\n\n", getpid(), message);
	send_message(server_pid, message);
	return (0);
}
