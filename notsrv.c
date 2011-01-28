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

#include <event2/dns.h>
#include <event2/dns_struct.h>
#include <event2/util.h>
#include <event2/event.h>

#include <sys/socket.h>

#include <stdio.h>
#include <string.h>
//#include <assert.h>

/* 
 *Listening Port may be given in compilation.
 * If not use this one, since 53 requires root priv
 */
#ifndef LISTEN_PORT
#define LISTEN_PORT 5359
#endif

#define SIC_IPV4_ARPA "1.0.0.10.in-addr.arpa"
#define SIC_IPV6_ARPA ("1.0.0.0.0.0.0.0.0.0.0.0.0.0.0.0."         \
                             "0.0.0.0.0.0.0.0.0.0.0.0.0.c.e.f.ip6.arpa")

const ev_uint8_t SIC_IPV4[] = { 10, 0, 0, 1 };
const ev_uint8_t SIC_IPV6[] = { 0xfe,0xc0,
				0,0,0,0,
				0,0,0,0,
				0,0,0,1 };

#define TTL 10

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

    for (i=0; i < request->nquestions; ++i) {
        const struct evdns_server_question *q = request->questions[i];
        int ok=-1;
        /* We don't use regular strcasecmp here, since we want a locale-
           independent comparison. */
        if (0 == evutil_ascii_strcasecmp(q->name, SIC_IPV4_ARPA)) {
            if (q->type == EVDNS_TYPE_PTR)
                ok = evdns_server_request_add_ptr_reply(
                       request, NULL, q->name, "SHARING", TTL);
	} else if (0 == evutil_ascii_strcasecmp(q->name,SIC_IPV6_ARPA)) {
            if (q->type == EVDNS_TYPE_PTR)
                ok = evdns_server_request_add_ptr_reply(
                       request, NULL, q->name, "SHARING", TTL);
	} else {
		if (q->type == EVDNS_TYPE_A)
			ok = evdns_server_request_add_a_reply(
					request, q->name, 1,SIC_IPV4,TTL);
		else if (q->type == EVDNS_TYPE_AAAA)
                ok = evdns_server_request_add_aaaa_reply(
                       request, q->name, 1, SIC_IPV6,TTL) ;

		else {
			error = DNS_ERR_NOTEXIST;
		}
	}
	if (ok<0 && error==DNS_ERR_NONE)
		error = DNS_ERR_SERVERFAILED;

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
    listenaddr.sin_port = htons(LISTEN_PORT);
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


