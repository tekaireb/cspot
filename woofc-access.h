#ifndef WOOFC_ACCESS_H
#define WOOFC_ACCESS_H

int WooFValidURI(const char *str);
int WooFNameSpaceFromURI(const char *woof_uri_str, char *woof_namespace, int len);
int WooFNameFromURI(const char *woof_uri_str, char *woof_name, int len);
int WooFIPAddrFromURI(const char *woof_uri_str, char *woof_ip, int len);
unsigned int WooFPortHash(const char *woof_ns);
int WooFLocalIP(char *ip_str, int len);
int WooFPortFromURI(const char *woof_uri_str, int *woof_port);

unsigned long WooFMsgPut(const char *woof_name, const char *hand_name, void *element, unsigned long el_size);
unsigned long WooFMsgGetElSize(const char *woof_name);
int WooFMsgServer (const char *woof_ns);

int WooFURINameSpace(const char *woof_uri_str, char *woof_namespace, int len);

/*
 * 2 minute timeout
 */
#define WOOF_MSG_REQ_TIMEOUT (120000)

#define WOOF_MSG_THREADS (5)

#define WOOF_MSG_PUT (1)
#define WOOF_MSG_GET_EL_SIZE (2)
#define WOOF_MSG_GET (3)
#define WOOF_MSG_GET_TAIL (4)
#define WOOF_MSG_GET_LATEST_SEQNO (5)
#define WOOF_MSG_GET_DONE (6)

#define WOOF_MSG_CACHE_SIZE (100)

#endif

