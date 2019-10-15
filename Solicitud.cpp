#include "Solicitud.h"
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

Solicitud::Solicitud() : msjId(0)
{
	socketLocal = new SocketDatagrama(0);
}

char * Solicitud::doOperation(char *IP, int puerto, int operationId, const char *arguments)
{
	int bytes_env, bytes_recv, times = 0;

	// Crear mensaje que se envía:
	struct mensaje cmensaje;
    cmensaje.messageType = 0;
    cmensaje.requestId = ++msjId;
    cmensaje.operationId = operationId;
    strcpy(cmensaje.arguments, arguments);
	// Adjuntar al paquete datagrama:
	PaqueteDatagrama paquete_env = PaqueteDatagrama(&cmensaje, sizeof(cmensaje), IP, puerto);
    PaqueteDatagrama paquete_recv = PaqueteDatagrama(MAX_BUFF_TAM);

    do
    {
    	// Enviar:
    	bytes_env = socketLocal->enviaMensaje(paquete_env);
        // Recibir:
        bytes_recv = socketLocal->recibeTimeout(paquete_recv, 0, 500000);

    } while (++times < 7 && bytes_recv < 0);

    return paquete_recv.obtieneMensaje()->arguments;
}
