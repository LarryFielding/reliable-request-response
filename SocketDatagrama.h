#ifndef SOCKET_DATAGRAMA_H_
#define SOCKET_DATAGRAMA_H_

#include "PaqueteDatagrama.h"

#include <netinet/in.h>

#define MAX_BUFF_TAM 65507

class SocketDatagrama
{
public:

	/**
	 * @brief Crea un socket de tipo datagrama e inicializa
	 * los datos necesarios para la comunicación.
	 * @details Este constructor se debe usar preferiblemente en
	 * el servidor con un número de puerto conocido (diferente de 0).
	 * En el caso de un cliente se puede utilizar 0 como puerto
	 * para que sea asignado por el sistema, sin embargo este
	 * constructor no permite asignar la IP del servidor al que
	 * se desea enviar mensajes (direccionForanea)
	 * 
	 * @param puerto Número de puerto.
	 */
	SocketDatagrama(int puerto);
	
	~SocketDatagrama();

	/**
	 * @brief Recibe un paquete de tipo datagrama.
	 * @details Debe prepararse al PaqueteDatagrama que recibe
	 * el mensaje con el tamaño máximo de buffer. Una vez
	 * que se recibe el mensaje debe asignarse al objeto
	 * PaqueteDatagrama la dirección ip y puerto del host remoto
	 * que envió el mensaje.
	 * 
	 * @param p PaqueteDatagrama con memoria reservada dinámicamente
	 * para recibir un mensaje,
	 * @return Número de bytes recibidos.
	 */
	int recibe(PaqueteDatagrama & p);

	/**
	 * @brief Envía un paquete de tipo datagrama configurado
	 * previamente con el mensaje e información del host que
	 * envía el mensaje.
	 * @details [long description]
	 * 
	 * @param p Paquete datagrama configurado previamente.
	 * @return Número de bytes enviados.
	 */
	int envia(PaqueteDatagrama & p);

	/**
	 * @brief Envía un paquete de tipo datagrama. El contenido
	 * es una struct mensaje.
	 * @details Diseñado para el protocolo petición-respuesta.
	 * 
	 * @param p Paquete datagrama configurado previamente.
	 * @return Número de bytes enviados.
	 */
	int enviaMensaje(PaqueteDatagrama & p);

	int recibeMensaje(PaqueteDatagrama & p);

	int recibeTimeout(PaqueteDatagrama & p, time_t segundos, suseconds_t microsegundos);

	const void * obtieneDireccionForanea();

	int obtienePuertoForaneo();
	
private:

	struct sockaddr_in direccionLocal;
	struct sockaddr_in direccionForanea;
	struct timeval timeout;
	int s; //ID socket
};


#endif