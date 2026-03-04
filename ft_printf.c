/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traomeli <traomeli@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 08:00:05 by traomeli          #+#    #+#             */
/*   Updated: 2026/02/17 16:38:05 by traomeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	if (!format)
		return (-1);
	count = 0;
	va_start(args, format);
	i = 0;
	while (format[count])
	{
		if (format[count] == '%')
			i += ft_util(args, (format[++count]));
		else
			i += ft_putchar(format[count]);
		count++;
	}
	va_end(args);
	return (i);
}

int	ft_util(va_list args, char sign)
{
	if (sign == 'd' || sign == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (sign == 'x')
		return (ft_hexa(va_arg(args, unsigned int), "0123456789abcdef"));
	if (sign == 'X')
		return (ft_hexa(va_arg(args, unsigned int), "0123456789ABCDEF"));
	if (sign == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (sign == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (sign == 'p')
		return (ft_ptr(va_arg(args, void *)));
	if (sign == 'u')
		return (ft_putnbr_usd(va_arg(args, unsigned int)));
	if (sign == '%')
		return (ft_putchar('%'));
	return (0);
}

static int	ft_ptr(void *ptr)
{
	int	count;

	count = 0;
	if (!ptr)
	{
		count = 5;
		return (write(1, "(nil)", 5));
	}
	count += write(1, "0x", 2);
	count += ft_hexa((unsigned long)ptr, "0123456789abcdef");
	return (count);
}

static int	ft_putnbr_usd(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb >= 10)
	{
		count += ft_putnbr_usd(nb / 10);
	}
	count += ft_putchar(nb % 10 + '0');
	return (count);
}
