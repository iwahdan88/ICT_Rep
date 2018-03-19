all: server client

server: server.c
	gcc -g -Wall $< -o $@ `pkg-config libwebsockets --libs --cflags`
client: client.c
	gcc -g -Wall $< -o $@ `pkg-config libwebsockets --libs --cflags`
server_rpi: server_rpi.c
	gcc -g -Wall $< -o $@ `pkg-config libwebsockets --libs --cflags`
client_rpi: client_rpi.c
	gcc -g -Wall $< -o $@ `pkg-config libwebsockets --libs --cflags`

clean:
	rm -f server
	rm -rf server.dSYM
	rm -f client
	rm -rf client.dSYM
	rm -f server_rpi
	rm -rf server_rpi.dSYM
	rm -f client_rpi
	rm -rf client_rpi.dSYM
