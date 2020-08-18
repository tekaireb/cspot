#include "dht.h"
#include "dht_utils.h"
#include "monitor.h"
#include "woofc.h"

#include <stdlib.h>
#include <string.h>

int h_subscribe(WOOF* wf, unsigned long seq_no, void* ptr) {
    log_set_tag("subscribe");
    log_set_level(DHT_LOG_INFO);
    // log_set_level(DHT_LOG_DEBUG);
    log_set_output(stdout);

    DHT_SUBSCRIBE_ARG arg = {0};
    if (monitor_cast(ptr, &arg) < 0) {
        log_error("failed to call monitor_cast");
        monitor_exit(ptr);
        exit(1);
    }

    char subscription_woof[DHT_NAME_LENGTH];
    sprintf(subscription_woof, "%s_%s", arg.topic_name, DHT_SUBSCRIPTION_LIST_WOOF);
    if (!WooFExist(subscription_woof)) {
        log_error("topic %s doesn't exist", arg.topic_name);
        monitor_exit(ptr);
        exit(1);
    }
    DHT_SUBSCRIPTION_LIST list = {0};
    if (get_latest_element(subscription_woof, &list) < 0) {
        log_error("failed to get latest subscription list of %s: %s", subscription_woof, dht_error_msg);
        monitor_exit(ptr);
        exit(1);
    }

    if (list.size == DHT_MAX_SUBSCRIPTIONS) {
        log_error("maximum number of subscriptions %d has been reached", list.size);
        monitor_exit(ptr);
        return 1;
    }

    memcpy(list.handlers[list.size], arg.handler, sizeof(list.handlers[list.size]));
    memcpy(list.handler_namespace[list.size], arg.handler_namespace, sizeof(list.handler_namespace[list.size]));
    list.size += 1;
    log_debug("number of subscription: %d", list.size);
    int i;
    for (i = 0; i < list.size; ++i) {
        log_debug("[%d] %s/%s", i, list.handler_namespace[i], list.handlers[i]);
    }

    unsigned long seq = WooFPut(subscription_woof, NULL, &list);
    if (WooFInvalid(seq)) {
        log_error("failed to update subscription list %s", arg.topic_name);
        monitor_exit(ptr);
        exit(1);
    }
    log_info("%s/%s subscribed to topic %s", arg.handler_namespace, arg.handler, arg.topic_name);

    monitor_exit(ptr);
    return 1;
}
