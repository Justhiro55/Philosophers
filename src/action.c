/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:07:21 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/09/24 18:39:26 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->dead_mutex);
	if (get_time() - philo->last_meal_time > philo->info->time_to_die)
	{
		pthread_mutex_unlock(&philo->info->dead_mutex);
		return ;
	}
	if (philo->info->finish_count == philo->info->philo_num)
	{
		pthread_mutex_unlock(&philo->info->dead_mutex);
		return ;
	}
	if (philo->info->finish_count != philo->info->philo_num
		&& philo->info->dead != 1)
		print(philo, "is thinking");
	pthread_mutex_unlock(&philo->info->dead_mutex);
}

void	sleep_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->dead_mutex);
	if (philo->info->dead == 1)
	{
		pthread_mutex_unlock(&philo->info->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->info->dead_mutex);
	pthread_mutex_lock(&philo->info->dead_mutex);
	if (philo->info->finish_count == philo->info->philo_num)
	{
		pthread_mutex_unlock(&philo->info->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->info->dead_mutex);
	usleep(philo->info->time_to_sleep * 1000);
	if (get_time() - philo->last_meal_time > philo->info->time_to_die)
		return ;
}

int	monitor_count(t_philo *philo)
{
	if (philo->eat_count == philo->info->must_eat && philo->finish_flag == 0)
	{
		philo->finish_flag++;
		pthread_mutex_lock(&philo->info->write);
		philo->info->finish_count++;
		pthread_mutex_unlock(&philo->info->write);
	}
	pthread_mutex_lock(&philo->info->write);
	if (philo->info->finish_count != philo->info->philo_num
		&& philo->info->dead != 1)
	{
		pthread_mutex_unlock(&philo->info->write);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->write);
	return (0);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->dead_mutex);
	if (philo->info->finish_count == philo->info->philo_num)
	{
		pthread_mutex_unlock(&philo->info->dead_mutex);
		return ;
	}
	if (monitor_count(philo) == 1)
		print(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->info->dead_mutex);
	pick_up_forks(philo);
	pthread_mutex_lock(&philo->info->dead_mutex);
	if (monitor_count(philo) == 1)
		print(philo, "has taken a fork");
	philo->last_meal_time = get_time();
	if (monitor_count(philo) == 1)
		print(philo, "is eating");
	pthread_mutex_unlock(&philo->info->dead_mutex);
	usleep(philo->info->time_to_eat * 1000);
	put_down_forks(philo);
	if (monitor_count(philo) == 1)
		print(philo, "is sleeping");
	philo->eat_count++;
}
