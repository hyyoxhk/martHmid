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
