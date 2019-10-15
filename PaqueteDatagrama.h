#ifndef PAQUETE_DATAGRAMA_H_
#define PAQUETE_DATAGRAMA_H_

#include "mensaje.h"


class PaqueteDatagrama
{
private:
    char *datos; //Almacena los datos
    char ip[16]; //Almacena la IP
    unsigned int longitud; //Almacena la longitude de la cadena de datos
    int puerto; //Almacena el puerto
    struct mensaje request_reply_msg; // Mensaje del protocolo petición-respuesta
    
public:
    
    /**
     * @brief Crea un paquete de envío tipo datagrama.
     * @details [long description]
     * 
     * @param payload Es la cadena a enviarse en el datagrama.
     * @param int Es la longitud de la cadena (strlen(payload))
     * @param ipAddress [description]
     * @param port [description]
     */
    PaqueteDatagrama(const char * payload, unsigned int size, const char * ipAddress, int port);


    /**
     * @brief Crea un paquete de envío tipo datagrama.
     * @details El contenido del paquete es un struct mensaje,
     * específico para usar con el protocolo petición-respuesta
     * 
     * @param mensaje Mensaje para protocolo petición-respuesta.
     * @param int Tamaño del mensaje.
     * @param ipAddress IP destino.
     * @param port Puerto destino.
     */
    PaqueteDatagrama(struct mensaje * msj, unsigned int size, const char * ipAddress, int port);

    /**
     * @brief Crea un mensaje vacío de una longitud
     * determinada para la recepción.
     * @details [long description]
     * 
     * @param int El tamaño del mensaje que se va a recbir.
     */
    PaqueteDatagrama(unsigned int size);

    /**
     * @brief Libera la memoria dinámica reservada para
     * los datos en el constructor.
     * @details [long description]
     */
    ~PaqueteDatagrama();

    /**
     * @brief Obtiene dirección IP del host remoto al que
     * se envía o del que se recibe.
     * @details [long description]
     * @return [description]
     */
    char * obtieneDireccion();

    /**
     * @brief Obtiene el tamaño de los datos que se
     * envían o se reciben.
     * @details [long description]
     * @return [description]
     */
    unsigned int obtieneLongitud();

    /**
     * @brief Obtiene el puerto del host remoto del
     * que se envía o del que se recibe.
     * @details [long description]
     * @return [description]
     */
    int obtienePuerto();

    /**
     * @brief Regresa los datos almacenados en
     * el miembro datos de la clase.
     * @details [long description]
     * @return [description]
     */
    char * obtieneDatos();

    /**
     * @brief Inicializa el miembro puerto.
     * @details [long description]
     * 
     * @param  [description]
     */
    void inicializaPuerto(int puerto);

    /**
     * @brief Inicializa el miembro IP.
     * @details [long description]
     * 
     * @param r [description]
     */
    void inicializaIp(char * ip);

    /**
     * @brief Inicializa los datos que se almacenan
     * en el miembro datos.
     * @details [long description]
     * 
     * @param r [description]
     */
    void inicializaDatos(char * datos);


    struct mensaje * obtieneMensaje();

    void inicializaMensaje(struct mensaje * msj);
};

#endif
