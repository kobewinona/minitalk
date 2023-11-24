/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:22:14 by dklimkin          #+#    #+#             */
/*   Updated: 2023/11/23 15:22:14 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	send_message(int pid, char *message)
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
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(500);
			k--;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*message;
	int		pid;

	if (argc != 3)
	{
		ft_printf("please provide PID and a string\n");
		exit(1);
	}
	pid = ft_atoi(argv[1]);
	if (!pid)
	{
		ft_printf("please provide correct PID\n");
		exit (1);
	}
	message = argv[2];
	ft_printf("client says:\n\n%s ⸜(ˆᗜˆ˵ )⸝\n\n\n", message);
	send_message(pid, message);
	return (0);
}
