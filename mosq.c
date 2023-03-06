// SPDX-License-Identifier: Commercial
/*
 * Copyright (C) 2022 He Yong <hyyoxhk@163.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <mosquitto.h>

#include "pctrl.h"
#include "mosq.h"
#include "smarthmid.h"


// static void init_config(smarthmid_cfg_t *cfg, int pub_or_sub)
// {
// 	memset(cfg, 0, sizeof(*cfg));
// 	cfg->port = PORT_UNDEFINED;
// 	cfg->max_inflight = 20;
// 	cfg->keepalive = 60;
// 	cfg->clean_session = true;
// 	cfg->protocol_version = MQTT_PROTOCOL_V5;
// }

// int mosq_id_generate(smarthmid_cfg_t *cfg)
// {

// 	cfg->id = malloc(10);
// 	if(!cfg->id){
// 		fprintf(stderr, "Error: Out of memory.\n");
// 		mosquitto_lib_cleanup();
// 		return MOSQ_ERR_NOMEM;
// 	}
// 	snprintf(cfg->id, 10, "%d", getpid());

// 	return MOSQ_ERR_SUCCESS;
// }

// int mosq_config_parse(smarthmid_cfg_t *cfg, int argc, char *argv[])
// {
// 	return 0;
// }

static void on_subscribe_cb(struct mosquitto *mosq, void *obj, int mid,
				  int qos_count, const int *granted_qos)
{

}
static void on_connect_cb(struct mosquitto *mosq, void *obj, int reason_code)
{
	int rc;

	printf("on_connect: %s\n", mosquitto_connack_string(reason_code));
	if(reason_code != 0)
		mosquitto_disconnect(mosq);

	rc = mosquitto_subscribe(mosq, NULL, "/topic/switch", 1);
	if(rc != MOSQ_ERR_SUCCESS) {
		fprintf(stderr, "Error subscribing: %s\n", mosquitto_strerror(rc));
		mosquitto_disconnect(mosq);
	}
}

static void on_publish_cb(struct mosquitto *mosq, void *obj, int mid)
{
	printf("Message with mid %d has been published.\n", mid);
}

static void on_message_cb(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{

}

// void *mosq_initializer(void *data)
// {
// 	smarthmid_cfg_t *cfg = data;
// 	struct mosquitto *mosq;
// 	int rc;

// 	mosquitto_lib_init();

// 	mosq = mosquitto_new(cfg->id, cfg->clean_session, cfg);
// 	if (!mosq) {
// 		switch(errno) {
// 		case ENOMEM:
// 			fprintf(stderr, "Error: Out of memory.\n");
// 			break;
// 		case EINVAL:
// 			fprintf(stderr, "Error: Invalid id and/or clean_session.\n");
// 			break;
// 		}
// 		goto cleanup;
// 	}

// 	//mosq_opts_set

// 	//if(cfg.debug) {
// 	//	mosquitto_log_callback_set(g_mosq, my_log_callback);
// 	//}

// 	mosquitto_connect_callback_set(mosq, on_connect_cb);
// 	mosquitto_subscribe_callback_set(mosq, on_subscribe_cb);
// 	mosquitto_publish_callback_set(mosq, on_publish_cb);
// 	mosquitto_message_callback_set(mosq, on_message_cb);

// 	rc = mosquitto_connect(mosq, cfg->host, cfg->port, cfg->keepalive);
// 	if(rc != MOSQ_ERR_SUCCESS){
// 		mosquitto_destroy(mosq);
// 		fprintf(stderr, "Error: %s\n", mosquitto_strerror(rc));
// 		exit(2);
// 	}

// 	mosquitto_loop_forever(mosq, -1, 1);

// cleanup:
// 	mosquitto_destroy(mosq);
// 	mosquitto_lib_cleanup();
// 	return (void *)0;
// }

void *mosq_initializer(void *data)
{
	struct mosquitto *mosq;
	int rc;

	mosquitto_lib_init();

	mosq = mosquitto_new(NULL, true, NULL);
	if (!mosq) {
		switch(errno) {
		case ENOMEM:
			fprintf(stderr, "Error: Out of memory.\n");
			break;
		case EINVAL:
			fprintf(stderr, "Error: Invalid id and/or clean_session.\n");
			break;
		}
		goto cleanup;
	}

	mosquitto_connect_callback_set(mosq, on_connect_cb);
	mosquitto_subscribe_callback_set(mosq, on_subscribe_cb);
	mosquitto_publish_callback_set(mosq, on_publish_cb);
	mosquitto_message_callback_set(mosq, on_message_cb);

	rc = mosquitto_connect(mosq, "127.0.0.1", 1883, 60);
	if(rc != MOSQ_ERR_SUCCESS){
		mosquitto_destroy(mosq);
		fprintf(stderr, "Error: %s\n", mosquitto_strerror(rc));
		exit(2);
	}

	mosquitto_loop_forever(mosq, -1, 1);

cleanup:
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
	return (void *)0;
}
