#include "df.h"
#include "woofc.h"
#include "dfinterface.h"

#include <iostream>
#include <fstream>

extern "C" int output_handler(WOOF* wf, unsigned long seqno, void* ptr) {
    std::cout << "OUTPUT HANDLER STARTED" << std::endl;

    operand* result = static_cast<operand*>(ptr);

    std::cout << "wf: " << WoofGetFileName(wf) << std::endl;
    std::cout << "seqno: " << seqno << std::endl;
    std::cout << "operand: " << result->value << std::endl;

    // Get name of this woof
    std::string woof_name(WoofGetFileName(wf));
    
    // Extract id
    unsigned long id = get_id_from_woof_path(woof_name);

    //Extract namespace
    int ns = get_ns_from_woof_path(woof_name);

    // Exit if double-fired
    if (seqno > 1) {
        operand prev;
        woof_get(woof_name, &prev, seqno - 1);
        if (prev.seq == result->seq) {
            std::cout << "[" << woof_name << "] double-fired, exiting" << std::endl;
            std::cout << "OUTPUT HANDLER DONE (early)" << std::endl;
            return 0;
        }
    }

    /* Get subscribers */

    std::string submap_woof = generate_woof_path(SUBSCRIBER_MAP_WOOF_TYPE, ns);
    std::string subdata_woof = generate_woof_path(SUBSCRIBER_DATA_WOOF_TYPE, ns);
    unsigned long start_idx, end_idx;
    unsigned long last_seq = woof_last_seq(submap_woof);

    // Get data range (TODO: factor out into function for woofmap)
    woof_get(submap_woof, &start_idx, id);
    if (id == last_seq) {
        end_idx = woof_last_seq(subdata_woof) + 1;
    } else {
        woof_get(submap_woof, &end_idx, id + 1);
    }

    std::cout << "start_idx: " << start_idx << ", end_idx: " << end_idx << std::endl;

    // Iterate over subscribers and push to respective woofs
    for (unsigned long i = start_idx; i < end_idx; i++) {
        // Get subscriber data
        subscriber sub;
        woof_get(subdata_woof, &sub, i);

        std::string subscriber_woof = generate_woof_path(SUBSCRIPTION_EVENTS_WOOF_TYPE, sub.ns, sub.id);
        subscription_event subevent(sub.ns, sub.id, sub.port, result->seq);
        woof_put(subscriber_woof, "subscription_event_handler", &subevent);

        std::cout << "{ns=" << sub.ns << ", id=" << sub.id << ", port=" << sub.port << ", seqno=" << seqno << "}" << std::endl;
    }

    std::cout << "OUTPUT HANDLER DONE" << std::endl;
    
    return 0;
}