#include "dht.h"
#include "dht_utils.h"
#include "monitor.h"
#include "woofc.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int r_set_successor(WOOF* wf, unsigned long seq_no, void* ptr) {
    DHT_SUCCESSOR_INFO* arg = (DHT_SUCCESSOR_INFO*)ptr;

    log_set_tag("set_successor");
    log_set_level(DHT_LOG_INFO);
    // log_set_level(DHT_LOG_DEBUG);
    log_set_output(stdout);

    DHT_NODE_INFO node = {0};
    if (get_latest_node_info(&node) < 0) {
        log_error("couldn't get latest node info: %s", dht_error_msg);
        monitor_exit(ptr);
        exit(1);
    }

    unsigned long seq = WooFPut(DHT_SUCCESSOR_INFO_WOOF, NULL, arg);
    if (WooFInvalid(seq)) {
        log_error("failed to set successor");
        exit(1);
    }
    log_debug("set successor[0] to %s", successor_addr(arg, 0));
    log_debug("set successor[1] to %s", successor_addr(arg, 1));
    log_debug("set successor[2] to %s", successor_addr(arg, 2));
    // #ifdef DEBUG
    // printf("%s successor set to %s at %" PRIu64 " (%lu)\n",
    //        arg->triggered_by,
    //        node.addr,
    //        successor_addr(arg, 0),
    //        get_milliseconds(),
    //        WooFGetLatestSeqno(BLOCKED_NODES_WOOF));
    // #endif

    return 1;
}
