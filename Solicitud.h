#ifndef SOLICITUD_H_
#define SOLICITUD_H_

#include "SocketDatagrama.h"

class Solicitud
{
public:
	Solicitud();
	
	char * doOperation(char *IP, int puerto, int operationId, const char *arguments);

private:
	SocketDatagrama * socketLocal;

	unsigned int msjId;
};


#endif