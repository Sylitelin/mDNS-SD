#ifndef __MDNSSD_ITF_H
#define __MDNSSD_ITF_H

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#if defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <io.h>
#include <inaddr.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#endif


#define MAX_ANSWERS (256)

typedef struct {
	char *name;
	char *value;
} txt_attr;

typedef struct {
  struct mDNSItem_s {
	char* name; // name from PTR
	char* hostname; // from SRV
	struct in_addr addr; // from A
	unsigned short port; // from SRVFound;
	txt_attr *attr;
	int	attr_count;
  } items[MAX_ANSWERS];
  int count;
} DiscoveredList;

bool 	query_mDNS(int sock, bool *query_ctrl, char* query_arg, DiscoveredList* dlist, int runtime);
int 	init_mDNS(int dbg, struct in_addr host);
void 	close_mDNS(int sock, bool *query_ctrl);
void 	free_discovered_list(DiscoveredList* dlist);
#endif
