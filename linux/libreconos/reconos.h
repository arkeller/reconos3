#ifndef RECONOS_H
#define RECONOS_H

#include "config.h"

#include <pthread.h>

#define RECONOS_TYPE_MBOX      0x00000001
#define RECONOS_TYPE_SEM       0x00000002
#define RECONOS_TYPE_MUTEX     0x00000004
#define RECONOS_TYPE_COND      0x00000008
#define RECONOS_TYPE_RQ        0x00000010

#define RECONOS_CMD_THREAD_GET_INIT_DATA 0x000000A0
#define RECONOS_CMD_THREAD_DELAY         0x000000A1 // ToDo
#define RECONOS_CMD_THREAD_EXIT          0x000000A2
#define RECONOS_CMD_THREAD_YIELD         0x000000A3 // ToDo
#define RECONOS_CMD_THREAD_RESUME        0x000000A4 // ToDo
#define RECONOS_CMD_THREAD_LOAD_STATE    0x000000A5 // ToDo
#define RECONOS_CMD_THREAD_STORE_STATE   0x000000A6 // ToDo

#define RECONOS_CMD_SEM_POST       0x000000B0
#define RECONOS_CMD_SEM_WAIT       0x000000B1

#define RECONOS_CMD_MUTEX_LOCK     0x000000C0
#define RECONOS_CMD_MUTEX_UNLOCK   0x000000C1
#define RECONOS_CMD_MUTEX_TRYLOCK  0x000000C2 // Not tested, yet

#define RECONOS_CMD_COND_WAIT      0x000000D0 // Not tested, yet
#define RECONOS_CMD_COND_SIGNAL    0x000000D1 // Not tested, yet
#define RECONOS_CMD_COND_BROADCAST 0x000000D2 // Not tested, yet

#define RECONOS_CMD_RQ_RECEIVE     0x000000E0 // ToDo
#define RECONOS_CMD_RQ_SEND        0x000000E1 // ToDo

#define RECONOS_CMD_MBOX_GET       0x000000F0
#define RECONOS_CMD_MBOX_PUT       0x000000F1
#define RECONOS_CMD_MBOX_TRYGET    0x000000F2 // ToDo
#define RECONOS_CMD_MBOX_TRYPUT    0x000000F3 // ToDo




struct reconos_resource {
	void * ptr;       // pointer to resource (can be an object or a handle)
	uint32 type;      // integer identifying the resource type
};

struct reconos_hwt {
	pthread_t                delegate;
	int                      slot;
	struct reconos_resource* resources;
	int                      num_resources;
	void *                   init_data;
};

#define SLOT_FLAG_RESET 0x00000001

struct reconos_process
{
	uint32 page_faults;
	int proc_control_fsl_a; // proc_control initiates requests
	int proc_control_fsl_b; // sw initiates requests
	pthread_t proc_control_thread;
	int slot_flags[MAX_SLOTS];
	int fd_cache;
};

extern struct reconos_process reconos_proc;

int reconos_init(int proc_ctrl_fsl_a, int proc_control_fsl_b);
int reconos_init_autodetect();

void cache_flush(void);

void proc_control_selftest();

void reconos_mmu_stats(uint32 * tlb_hits, uint32 * tlb_misses, uint32 * page_faults);

void reconos_hwt_setresources(struct reconos_hwt * hwt, struct reconos_resource * res, int num_resources);

void reconos_hwt_setinitdata(struct reconos_hwt * hwt, void * init_data);

int reconos_hwt_create(struct reconos_hwt * hwt, int slot, void * arg);

#endif

