all: cliente servidor
cliente: cliente.cpp Solicitud.o SocketDatagrama.o PaqueteDatagrama.o
	g++ cliente.cpp Solicitud.o SocketDatagrama.o PaqueteDatagrama.o -o cliente
servidor: servidor.cpp Respuesta.o SocketDatagrama.o PaqueteDatagrama.o
	g++ servidor.cpp Respuesta.o SocketDatagrama.o PaqueteDatagrama.o -o servidor
Solicitud.o: Solicitud.cpp Solicitud.h mensaje.h SocketDatagrama.o PaqueteDatagrama.o
	g++ Solicitud.cpp -c
Respuesta.o: Respuesta.cpp Respuesta.h SocketDatagrama.o PaqueteDatagrama.o
	g++ Respuesta.cpp -c
SocketDatagrama.o: SocketDatagrama.cpp SocketDatagrama.h PaqueteDatagrama.o
	g++ SocketDatagrama.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c
	