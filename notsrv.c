/*
 * ============================================================================
 *
 *       Filename:  stupiddns.c
 *
 *    Description:  just fittet the libevent example dns to sharing is caring
 *
 *        Version:  1.0
 *        Created:  26.01.2011 07:42:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  john (js), john@tuxcode.org
 *        Company:  tuxcode.org
 *
 * ============================================================================
 */
#include "config.h"
#include <event2/dns.h>
#include <event2/dns_struct.h>
#include <event2/util.h>
#include <event2/event.h>

#include <sys/socket.h>

#include <stdio.h>
#include <string.h>
//#include <assert.h>

const ev_uint8_t SIC_IPV4[] = STUPID_IP4 ;
const ev_uint8_t SIC_IPV6[] = STUPID_IP6 ;

#define TTL STUPID_TTL

/* This toy DNS server callback answers requests for stuff
 * pointin to the sic site
 */
void server_callback(struct evdns_server_request *request, void *data)
{
	int i;
	int error=DNS_ERR_NONE;
	/* We should try to answer all the questions.  Some DNS servers don't do
	   this reliably, though, so you should think hard before putting two
	   questions in one request yourself. */
	char * anam = NULL;
	char buf[128] ;

	for (i=0; i < request->nquestions; ++i) {
		const struct evdns_server_question *q = request->questions[i];
		int ok=-1;

		switch ( q->type )
		{
			case 	EVDNS_TYPE_PTR :
				if ( (0 == evutil_ascii_strcasecmp(q->name, STUPID_IP4_ARPA)) ||
						(0 == evutil_ascii_strcasecmp(
										 q->name,STUPID_IP6_ARPA) ) )
				{
					ok = evdns_server_request_add_ptr_reply(
							request, NULL, q->name, STUPID_HOSTNAME, TTL);
				}
				break;

			case EVDNS_TYPE_A :
				ok = evdns_server_request_add_a_reply(
						request, q->name, 1,SIC_IPV4,TTL);
				anam=(char*)q->name;
				break;

			case 	EVDNS_TYPE_AAAA:
				ok = evdns_server_request_add_aaaa_reply( 
						request, q->name, 1, SIC_IPV6,TTL);
				anam=(char*)q->name;
				break;

			case 	EVDNS_TYPE_NS:
				break;

			case  EVDNS_TYPE_CNAME:
			case  EVDNS_TYPE_SOA :
			case  EVDNS_TYPE_MX  :
			case  EVDNS_TYPE_TXT :
			default:
				break;

		}	/* -----  end switch  ----- */

		if (ok<0 && error==DNS_ERR_NONE)
			error = DNS_ERR_SERVERFAILED;

	}
	evdns_server_request_set_flags(request,EVDNS_FLAGS_AA );
	if (anam){
		snprintf(buf,127,"NS.%s.",anam);
		buf[128] =0;
		evdns_server_request_add_reply(request,EVDNS_AUTHORITY_SECTION ,STUPID_HOSTNAME,
				EVDNS_TYPE_NS, EVDNS_CLASS_INET, TTL, sizeof(STUPID_HOSTNAME) , 1,STUPID_HOSTNAME
				);
	}
	/* Now send the reply. */
	evdns_server_request_respond(request, error);
}





int main(int argc, char **argv)
{
    struct event_base *base;
    struct evdns_server_port *server;
    evutil_socket_t server_fd;
    struct sockaddr_in listenaddr;

    base = event_base_new();
    if (!base)
        return 1;

    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd < 0)
        return 1;
    memset(&listenaddr, 0, sizeof(listenaddr));
    listenaddr.sin_family = AF_INET;
    listenaddr.sin_port = htons(STUPID_LISTEN_PORT);
    listenaddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_fd, (struct sockaddr*)&listenaddr, sizeof(listenaddr))<0)
        return 1;

    server = evdns_add_server_port_with_base(base, server_fd, 0,
                                             server_callback, NULL);

    event_base_dispatch(base);

    evdns_close_server_port(server);
    event_base_free(base);

    return 0;
}


