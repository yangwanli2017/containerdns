#ifndef __DNSCONF_H__
#define __DNSCONF_H__

#include <stdint.h>
#include "zone.h"

#define DPDK_ARG_MAX_NUM 32

#ifndef MIN
#define MIN(v1, v2) ((v1) < (v2) ? (v1) : (v2))
#endif

struct zones_reload {
    char add_zone[ZONES_STR_LEN];
    char del_zone[ZONES_STR_LEN];
};

struct dpdk_config {
    char *argv[DPDK_ARG_MAX_NUM];
    int argc;
};

struct comm_config {
    char *zones;
    char *log_file;
    char *fwd_addrs;
    char *fwd_def_addrs;
    char *fwd_mode;
    uint16_t fwd_threads;
    uint16_t fwd_timeout;
    uint32_t fwd_mbuf_num;
    int ssl_enable;
    char *key_pem_file;
    char *cert_pem_file;
    uint16_t web_port;
    char *metrics_host;

    uint32_t all_per_second;
    uint32_t fwd_per_second;
    uint32_t client_num;
};

struct netdev_config {
    char *name_prefix;
    char *mode;
    uint32_t mbuf_num;
    uint16_t rxq_desc_num;
    uint16_t txq_desc_num;
    uint16_t rxq_num;
    uint16_t txq_num;

    uint32_t kni_mbuf_num;
    uint32_t kni_ip;
    char *kni_vip;
    uint32_t kni_gateway;
};

struct dns_config {
    struct dpdk_config dpdk;
    struct comm_config comm;
    struct netdev_config netdev;
};

extern struct dns_config *g_dns_cfg;

void config_file_load(char *cfgfile_path, char *proc_name);

int config_reload_pre_core(unsigned lcore_id);

int config_reload_proc(char *dns_cfgfile);

#endif
