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

char	g_char = 0;
int		g_bit = 0;

static void	signal_handler(int signum)
{
	g_char |= (signum == SIGUSR1);
	g_bit++;

	if (g_bit == 8)
	{
		write(1, &g_char, 1);
		g_bit = 0;
		g_char = 0;
	}
	else
		g_char <<= 1;
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_printf("˖⁺｡˚⋆˙₊˚✧  ੈ‧₊˚*‧.₊˚\n\nPID: %d | ( ᵔ ᵕ ᵔ)\n\n", pid);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause();
	return (0);
}
