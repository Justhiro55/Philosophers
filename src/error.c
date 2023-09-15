/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:53:20 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/09/15 20:57:27 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	num_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		return (ERROR);
	}
	if (str[i] == '+')
		i++;
	if (str[i] == '0')
		return (ERROR);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	error_check(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (num_check(argv[i]) == ERROR)
			return (ERROR);
		if (ft_atoi(argv[i]) == 0)
			return (ERROR);
	}
	return (SUCCESS);
}
