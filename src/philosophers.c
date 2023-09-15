/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:34:16 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/09/15 20:38:41 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*work(void *philo_ptr)
{
	t_philo		*philo;
	pthread_t	monitor_thread;

	philo = (t_philo *)philo_ptr;
	if (philo->id % 2 == 0)
		usleep(100);
	philo->last_meal_time = get_time();
	pthread_create(&monitor_thread, NULL, &monitor, philo->info);
	while (1)
	{
		if (check_finish(*philo) == ERROR)
			break ;
		eat(philo);
		if (check_finish(*philo) == ERROR)
			break ;
		sleep_philo(philo);
		think(philo);
		if (check_finish(*philo) == ERROR)
			break ;
	}
	pthread_join(monitor_thread, NULL);
	return (0);
}

void	*monitor(void *info_ptr)
{
	int		i;
	t_info	*info;

	info = (t_info *)info_ptr;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&info->dead_mutex);
		if (get_time() - info->philos[i].last_meal_time > info->time_to_die
			&& info->dead != 1)
		{
			info->dead = 1;
			pthread_mutex_unlock(&info->dead_mutex);
			print(&info->philos[i], "died");
			return (0);
		}
		pthread_mutex_unlock(&info->dead_mutex);
		if (info->philos[i].eat_count == info->must_eat
			&& info->philos[i].finish_flag == 0)
		{
			info->philos[i].finish_flag++;
			info->finish_count++;
		}
		if (info->finish_count == info->philo_num || info->dead == 1)
			break ;
		i++;
		if (i == info->philo_num)
			i = 0;
	}
	return (0);
}

void	exec_philosophers(t_info info)
{
	int			i;
	pthread_t	*th;

	i = -1;
	th = (pthread_t *)malloc(sizeof(pthread_t) * info.philo_num);
	if (th == NULL)
		return ;
	while (++i < info.philo_num)
	{
		usleep(10);
		pthread_create(&th[i], NULL, &work, &info.philos[i]);
	}
	i = 0;
	while (1)
		if (info.finish_count == info.philo_num || info.dead == 1)
			break ;
	i = -1;
	while (++i < info.philo_num)
		pthread_join(th[i], NULL);
	free(th);
}
