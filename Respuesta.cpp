#include "Respuesta.h"

#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;


Respuesta::Respuesta(int pl) : msjId(0)
{
	socketLocal = new SocketDatagrama(7200);
}

struct mensaje * Respuesta::getRequest(void)
{
	int bytes_recv, bytes_env;

	PaqueteDatagrama paquete_recv = PaqueteDatagrama(MAX_BUFF_TAM);
	bytes_recv = socketLocal->recibeMensaje(paquete_recv);

	if (bytes_recv >= 0)
    {
        char * ipRemota = paquete_recv.obtieneDireccion();
        int puertoRemoto = paquete_recv.obtienePuerto();
        
        cout << "Request ID: " << paquete_recv.obtieneMensaje()->requestId << endl;

        // Obtener numeros de la cadena y operarlos

        cout << "Depósito : $" << paquete_recv.obtieneMensaje()->arguments << ".00" <<endl;
    }

	return paquete_recv.obtieneMensaje();
}

void Respuesta::sendReply(char * respuesta)
{
	int bytes_env, bytes_recv;
    char ipRemota[INET_ADDRSTRLEN];

    // Crear mensaje que se envía:
    struct mensaje cmensaje;
    cmensaje.messageType = 1;
    cmensaje.requestId = ++msjId;
    cmensaje.operationId = deposito;
    strcpy(cmensaje.arguments, respuesta);

    inet_ntop(AF_INET, socketLocal->obtieneDireccionForanea(), ipRemota, INET_ADDRSTRLEN);

    // Adjuntar al paquete datagrama:
    PaqueteDatagrama paquete_env = PaqueteDatagrama(&cmensaje, sizeof(cmensaje), ipRemota, socketLocal->obtienePuertoForaneo());

    // Enviar:
    bytes_env = socketLocal->enviaMensaje(paquete_env);

    if (bytes_env < 0)
    {
        perror("Fallo en envio");
        exit(1);
    }

    //cout << "Respuesta enviada." << endl;
}
