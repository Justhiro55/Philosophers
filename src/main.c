/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 16:36:39 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/09/15 20:40:30 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo(int argc, char **argv);

void	case_one_philo(t_info *info)
{
	print(&info->philos[0], "has taken a fork");
	usleep(info->time_to_die * 1000);
	print(&info->philos[0], "died");
}

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf(ERROR_MSG);
		return (1);
	}
	philo(argc, argv);
	return (0);
}

void	clear_data(t_info *info)
{
	if (info->th)
		free(info->th);
	if (info->forks)
		free(info->forks);
	if (info->philos)
		free(info->philos);
}

void	philo(int argc, char **argv)
{
	t_info	info;
	int		i;

	i = 0;
	if (error_check(argc, argv) == ERROR)
		return ;
	if (set_param(&info, argc, argv) == ERROR)
		return ;
	info.philos = set_philosopher(info.philo_num, info);
	if (info.philos == NULL)
		return ;
	if (info.philo_num == 1)
	{
		case_one_philo(&info);
		clear_data(&info);
	}
	else
	{
		exec_philosophers(info);
		clear_data(&info);
	}
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q philo");
// }
