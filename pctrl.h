// SPDX-License-Identifier: Commercial
/*
 * Copyright (C) 2022 He Yong <hyyoxhk@163.com>
 */

#ifndef _PCTL_H_
#define _PCTL_H_

#include <pthread.h>

pthread_t start_thread(void *(* start_routine) (void *), void *arg);

#endif
