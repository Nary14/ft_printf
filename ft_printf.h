/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traomeli <traomeli@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 07:46:46 by traomeli          #+#    #+#             */
/*   Updated: 2026/02/17 11:19:17 by traomeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
// include section
# include <stdarg.h>
# include <unistd.h>

// prototype section
int	ft_putchar(int c);
int	ft_putnbr(int nb);
int	ft_putstr(char *c);
int	ft_hexa(unsigned long nbr, char *base);
int	ft_printf(const char *format, ...);
int	ft_util(va_list args, char sign);

#endif
