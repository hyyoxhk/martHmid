// SPDX-License-Identifier: Commercial
/*
 * Copyright (C) 2022 He Yong <hyyoxhk@163.com>
 */

#ifndef _PCTL_H_
#define _PCTL_H_

#include <pthread.h>

pthread_t start_thread(void *(* start_routine) (void *), void *arg);

void thread_ready(void);

void wait_threads_ready(void);

#endif
