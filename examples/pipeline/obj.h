/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2020 Intel Corporation
 */

#ifndef _INCLUDE_OBJ_H_
#define _INCLUDE_OBJ_H_

#include <stdint.h>
#include <sys/queue.h>

#include <rte_swx_pipeline.h>
#include <rte_swx_ctl.h>

#ifndef NAME_SIZE
#define NAME_SIZE 64
#endif

/*
 * obj
 */
struct obj;

struct obj *
obj_init(void);

/*
 * link
 */
#ifndef LINK_RXQ_RSS_MAX
#define LINK_RXQ_RSS_MAX                                   16
#endif

struct link_params_rss {
	uint32_t queue_id[LINK_RXQ_RSS_MAX];
	uint32_t n_queues;
};

struct link_params {
	struct {
		uint32_t n_queues;
		uint32_t queue_size;
		const char *mempool_name;
		struct link_params_rss *rss;
	} rx;

	struct {
		uint32_t n_queues;
		uint32_t queue_size;
	} tx;

	int promiscuous;
};

struct link {
	TAILQ_ENTRY(link) node;
	char name[NAME_SIZE];
	uint16_t port_id;
	uint32_t n_rxq;
	uint32_t n_txq;
};

struct link *
link_create(struct obj *obj,
	    const char *name,
	    struct link_params *params);

int
link_is_up(struct obj *obj, const char *name);

struct link *
link_find(struct obj *obj, const char *name);

struct link *
link_next(struct obj *obj, struct link *link);

#endif /* _INCLUDE_OBJ_H_ */
