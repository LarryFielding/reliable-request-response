#include "SocketDatagrama.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <iostream>

using namespace std;

SocketDatagrama::SocketDatagrama(int puerto)
{
	int opc = 1;

	/* Paso 1: crear el socket */
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
	{
		perror("No se pudo crear socket");
		exit(1);
	}

	/* Paso 2: llenar estructura (direccion local) */

	memset(&direccionLocal, 0, sizeof(direccionLocal));
	direccionLocal.sin_family = AF_INET;
	direccionLocal.sin_addr.s_addr = INADDR_ANY;
	direccionLocal.sin_port = htons(puerto);

	/* Paso 3: publicar direccion */

	if ((bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal))) < 0)
	{
		perror("Error al publicar");
		exit(1);
	}
}

SocketDatagrama::~SocketDatagrama() {}

int SocketDatagrama::recibe(PaqueteDatagrama &p)
{
	int bytes_recv;
	socklen_t tam_dir;
	char ipRemota[INET_ADDRSTRLEN];
	
	tam_dir = sizeof(direccionForanea);
	cout << "Esperando mensaje..." << endl;
	
	bytes_recv = recvfrom(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, &tam_dir);
	if (bytes_recv < 0)
	{
		perror("Error al recibir");
		exit(1);
	}
	/* Imprimir en consola la dirección y puerto del host remoto (asignarlas a PaqueteDatagrama)*/
	
	inet_ntop(AF_INET, &(direccionForanea.sin_addr), ipRemota, INET_ADDRSTRLEN);
	p.inicializaIp(ipRemota);
	p.inicializaPuerto(htons(direccionForanea.sin_port));
	
	return bytes_recv;
}

int SocketDatagrama::recibeMensaje(PaqueteDatagrama &p)
{
	int bytes_recv;
	socklen_t tam_dir;
	char ipRemota[INET_ADDRSTRLEN];
	
	tam_dir = sizeof(direccionForanea);

	struct mensaje temp;
	
	bytes_recv = recvfrom(s, &temp, sizeof(temp), 0, (struct sockaddr *) &direccionForanea, &tam_dir);
	if (bytes_recv < 0)
	{
		perror("Error al recibir");
		exit(1);
	}
	/* Imprimir en consola la dirección y puerto del host remoto (asignarlas a PaqueteDatagrama)*/
	
	inet_ntop(AF_INET, &(direccionForanea.sin_addr), ipRemota, INET_ADDRSTRLEN);
	p.inicializaIp(ipRemota);
	p.inicializaPuerto(htons(direccionForanea.sin_port));
	p.inicializaMensaje(&temp);
	
	return bytes_recv;
}

int SocketDatagrama::envia(PaqueteDatagrama &p)
{
	int bytes_env;
	socklen_t tam_dir;

	tam_dir = sizeof(direccionForanea);


	/* Llenar estructura (direccion remota) */
	memset(&direccionForanea, 0, sizeof(direccionForanea));
	direccionForanea.sin_family = AF_INET;
	direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
	direccionForanea.sin_port = htons(p.obtienePuerto());

	bytes_env = sendto(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, tam_dir);
	if (bytes_env < 0)
	{
		perror("Fallo en envio");
		exit(1);
	}

	return bytes_env;
}

int SocketDatagrama::enviaMensaje(PaqueteDatagrama &p)
{
	int bytes_env;
	socklen_t tam_dir;

	tam_dir = sizeof(direccionForanea);


	/* Llenar estructura (direccion remota) */
	memset(&direccionForanea, 0, sizeof(direccionForanea));
	direccionForanea.sin_family = AF_INET;
	direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
	direccionForanea.sin_port = htons(p.obtienePuerto());

	bytes_env = sendto(s, (struct TextMessage*)p.obtieneMensaje(), p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, tam_dir);
	if (bytes_env < 0)
	{
		printf("%d\n", p.obtieneLongitud());
		perror("Fallo en envio");
		exit(1);
	}

	return bytes_env;
}

int SocketDatagrama::recibeTimeout(PaqueteDatagrama & p, time_t segundos, suseconds_t microsegundos)
{

	int bytes_recv;
	socklen_t tam_dir;
	char ipRemota[INET_ADDRSTRLEN];
	
	tam_dir = sizeof(direccionForanea);

	struct mensaje temp;

	// Inicialización y uso del timeout:

	timeout.tv_sec = segundos;
	timeout.tv_usec = microsegundos;
	if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
	{
		perror("No se pudo establecer el timeout.\n");
		exit(1);
	}
	
	bytes_recv = recvfrom(s, &temp, sizeof(temp), 0, (struct sockaddr *) &direccionForanea, &tam_dir);
	if (bytes_recv < 0)
	{
		if (errno == EWOULDBLOCK)
		{
			fprintf(stderr, "Tiempo para recepción transcurrido\n");
		}
		else
		{
			fprintf(stderr, "Error en recvfrom\n");
		}
	}
	/* Imprimir en consola la dirección y puerto del host remoto (asignarlas a PaqueteDatagrama)*/
	
	inet_ntop(AF_INET, &(direccionForanea.sin_addr), ipRemota, INET_ADDRSTRLEN);
	p.inicializaIp(ipRemota);
	p.inicializaPuerto(htons(direccionForanea.sin_port));
	p.inicializaMensaje(&temp);
	
	return bytes_recv;
}

const void * SocketDatagrama::obtieneDireccionForanea()
{
	return &(direccionForanea.sin_addr);
}

int SocketDatagrama::obtienePuertoForaneo()
{
	return htons(direccionForanea.sin_port);
}