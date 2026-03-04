/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traomeli <traomeli@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 07:59:40 by traomeli          #+#    #+#             */
/*   Updated: 2026/02/17 11:19:17 by traomeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr(int nb)
{
	int	count;

	count = 0;
	if (nb == -2147483648)
	{
		count += ft_putstr("-2147483648");
		return (count);
	}
	if (nb < 0)
	{
		count += ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10)
		count += ft_putnbr(nb / 10);
	count += ft_putchar(nb % 10 + '0');
	return (count);
}

int	ft_putstr(char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (write(1, "(null)", 6));
	while (c[i])
		i++;
	return (write(1, c, i));
}

int	ft_hexa(unsigned long nbr, char *base)
{
	unsigned long	len;
	int				count;

	count = 0;
	len = nbr;
	if (len >= 16)
	{
		count += ft_hexa(len / 16, base);
	}
	count += ft_putchar(base[len % 16]);
	return (count);
}
