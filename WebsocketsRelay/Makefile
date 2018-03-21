all: server client

server: server.c
	gcc -g -Wall $< -o $@ `pkg-config libwebsockets --libs --cflags`
client: client.c
	gcc -g -Wall $< -o $@ `pkg-config libwebsockets --libs --cflags`
server_ocu: wsServer_ocu.c
	gcc -g -Wall $< -o $@ `pkg-config libwebsockets --libs --cflags`
client_ocu: wsClient_ocu.c
	gcc -g -Wall $< -o $@ `pkg-config libwebsockets --libs --cflags`

clean:
	rm -f server
	rm -rf server.dSYM
	rm -f client
	rm -rf client.dSYM
	rm -f wsServer_ocu
	rm -rf wsServer_ocu.dSYM
	rm -f wsClient_ocu
	rm -rf wsClient_ocu.dSYM
