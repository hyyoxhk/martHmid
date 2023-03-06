// SPDX-License-Identifier: Commercial
/*
 * Copyright (C) 2022 He Yong <hyyoxhk@163.com>
 */

#include <stdio.h>
#include <unistd.h>

#include "pctrl.h"
#include "mosq.h"
#include "smarthmid.h"

static pthread_t mosq_daemon;

static smarthmid_cfg_t cfg;

int main(int argc, char const *argv[])
{
//mosquitto_pub -t /topic/switch -m "{\"Type\": \"switch\", \"DevId\": \"CF001CA0\", \"Status\": \"on\"}"
//mosquitto_pub -t /topic/switch -m "{\"Type\": \"switch\", \"DevId\": \"CF001CA0\", \"Status\": \"off\"}"
	

	mosq_daemon = start_thread(mosq_initializer, &cfg);

	/* wait for threads to be done before starting children */
	wait_threads_ready();

	pthread_join(mosq_daemon, NULL);
	//mosq_initializer();
	return 0;
}
 
