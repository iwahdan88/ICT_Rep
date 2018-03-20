#include <libwebsockets.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BUF 10

static int fd;
static char *pipeWs = "/tmp/websocpipe";

static struct lws *web_socket = NULL;

static int callback_example( struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len )
{
	switch( reason )
	{
		case LWS_CALLBACK_CLIENT_ESTABLISHED:
			lws_callback_on_writable( wsi );
			break;

		case LWS_CALLBACK_CLIENT_RECEIVE:
			/* Handle incomming messages here. */
			break;

		case LWS_CALLBACK_CLIENT_WRITEABLE:
		{
			unsigned char buf[LWS_SEND_BUFFER_PRE_PADDING + MAX_BUF + LWS_SEND_BUFFER_POST_PADDING];
			unsigned char *p = &buf[LWS_SEND_BUFFER_PRE_PADDING];
			int n = read(fd, p, MAX_BUF);
			lws_write( wsi, p, n, LWS_WRITE_TEXT );
			break;
		}

		case LWS_CALLBACK_CLOSED:
		case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
			web_socket = NULL;
			break;

		default:
			break;
	}

	return 0;
}

enum protocols
{
	PROTOCOL_EXAMPLE = 0,
	PROTOCOL_COUNT
};

static struct lws_protocols protocols[] =
{
	{
		"example-protocol",
		callback_example,
		0,
		MAX_BUF,
	},
	{ NULL, NULL, 0, 0 } /* terminator */
};

int main( int argc, char *argv[] )
{
	if(argc < 5)
	{
		printf("Please specify the <IP>  <Port> <socks_IP> <socks_port> to connect \n");
		return -1;
	}
	struct lws_context_creation_info info;
	memset( &info, 0, sizeof(info) );

	info.port = CONTEXT_PORT_NO_LISTEN;
	info.protocols = protocols;
	info.socks_proxy_address = argv[3];
	info.socks_proxy_port = atoi(argv[4]);
	info.gid = -1;
	info.uid = -1;

	/* Read from Pipe */

	fd = open(pipeWs, O_RDONLY);

	struct lws_context *context = lws_create_context( &info );

	time_t old = 0;
	while( 1 )
	{
		struct timeval tv;
		gettimeofday( &tv, NULL );

		/* Connect if we are not connected to the server. */
		if( !web_socket && tv.tv_sec != old)
		{
			struct lws_client_connect_info ccinfo = {0};
			ccinfo.context = context;
			ccinfo.address = argv[1];
			ccinfo.port = atoi(argv[2]);
			ccinfo.path = "/";
			ccinfo.host = lws_canonical_hostname( context );
			ccinfo.origin = "origin";
			ccinfo.protocol = protocols[PROTOCOL_EXAMPLE].name;
			web_socket = lws_client_connect_via_info(&ccinfo);
		}
		if( tv.tv_sec != old )
		{
			lws_callback_on_writable( web_socket );
		}

		lws_service( context, /* timeout_ms = */ 250 );
	}
	/* remove pipe */
	unlink(pipeWs);
	lws_context_destroy( context );

	return 0;
}
