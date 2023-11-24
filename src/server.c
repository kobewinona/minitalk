/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dklimkin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:21:42 by dklimkin          #+#    #+#             */
/*   Updated: 2023/11/23 15:21:43 by dklimkin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	handle_signal(int signum)
{
	static char	c;
	static int	bit;

	c = c | (signum == SIGUSR2);
	bit++;
	if (bit == 8)
	{
		write(1, &c, 1);
		bit = 0;
		c = 0;
	}
	else
		c <<= 1;
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_printf("˖⁺｡˚⋆˙₊˚✧  ੈ‧₊˚*‧.₊˚\n\nPID: %d | ( ᵔ ᵕ ᵔ) ", pid);
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
	return (0);
}
