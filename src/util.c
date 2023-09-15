/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 20:58:50 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/09/15 20:20:06 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_finish(t_philo philo)
{
	if (philo.info->finish_count == philo.info->philo_num
		|| philo.info->dead == 1)
		return (ERROR);
	return (SUCCESS);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->info->write);
	printf("%lu	%d %s\n", (unsigned long)get_time(), philo->id, action);
	pthread_mutex_unlock(&philo->info->write);
}
