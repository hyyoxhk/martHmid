// SPDX-License-Identifier: Commercial
/*
 * Copyright (C) 2022 He Yong <hyyoxhk@163.com>
 */

#ifndef _SMARTHMID_
#define _SMARTHMID_

#include <stdbool.h>
#include <mosquitto.h>

#define PORT_UNDEFINED -1

typedef struct {
	char *id;
	int protocol_version;
	int keepalive;
	char *host;
	int port;
	char *bind_address;
	unsigned int max_inflight;

	bool clean_session;


	char *database;

	mosquitto_property *connect_props;
	
} smarthmid_cfg_t;


#endif
