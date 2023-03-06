// SPDX-License-Identifier: Commercial
/*
 * Copyright (C) 2022 He Yong <hyyoxhk@163.com>
 */

#include <stdlib.h>

#include "pctrl.h"

/*
 * This allows waiting for initial threads to be ready before spawning subprocesses
 */
static int threads_towait = 0;
static pthread_mutex_t threads_towait_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t threads_towait_cond = PTHREAD_COND_INITIALIZER;

/*
 * This is used to spawn internal threads
 */
pthread_t start_thread(void *(* start_routine) (void *), void *arg)
{
	int ret;
	pthread_t id;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	pthread_mutex_lock(&threads_towait_lock);
	threads_towait++;
	pthread_mutex_unlock(&threads_towait_lock);

	ret = pthread_create(&id, &attr, start_routine, arg);
	if (ret) {
		exit(EXIT_FAILURE);
	}
	return id;
}

/*
 * Internal threads should signal they are ready if internal subprocesses
 * can be spawned after them
 */
void thread_ready(void)
{
	pthread_mutex_lock(&threads_towait_lock);
	threads_towait--;
	if (threads_towait == 0)
		pthread_cond_broadcast(&threads_towait_cond);
	pthread_mutex_unlock(&threads_towait_lock);
}

/*
 * Wait for all threads to have signaled they're ready
 */
void wait_threads_ready(void)
{
	pthread_mutex_lock(&threads_towait_lock);
	while (threads_towait != 0)
		pthread_cond_wait(&threads_towait_cond, &threads_towait_lock);
	pthread_mutex_unlock(&threads_towait_lock);
}

