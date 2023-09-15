/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:53:20 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/09/14 18:11:38 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	num_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		printf(ERROR_MSG);
		return (ERROR);
	}
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf(ERROR_MSG);
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
	}
	return (SUCCESS);
}
